/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:01 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/20 19:21:26 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	free_cmd_list(t_command *lst)
{
	t_command	*next_node;
	while (lst)
	{
		next_node = lst->next;
		free_command(lst);
		lst = next_node;
	}
}

void	print_cmd_list(t_command * lst)
{
	ft_printf("-----------LISTA DE COMANDOS-----------\n");
	while (lst)
	{
		print_command(lst);
		lst = lst->next;
	}
	ft_printf("------------------FIN------------------\n");
}

//Makes father process waiting for the children to ensure that all of them 
//finish correctly and avoid zombies process.
int	wait_for_children(int num_children)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_children)
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			return (-1);
		}
		i++;
	}
	return (0);
}

t_command	*lst_pipe_commands(t_mt *node, t_env *envp)
{
	t_mt		*select;
	t_mt		*prev;
	t_command	*first;
	t_command	*last;
	t_command	*new;

	select = node;
	first = NULL;
	while (select && ft_pmatch_str(select->data, "|", 1) == 0)
	{
		select->values.state = END;
		new = create_command(select->vect[LEFT], envp);
		select->vect[LEFT]->values.state = END;
		if (!first)
			first = new;
		else
			last->next = new;
		last = new;
		prev = select;
		select = select->vect[RIGHT]->vect[RIGHT];
	}
	new = create_command(prev->vect[RIGHT], envp);
	prev->vect[RIGHT]->values.state = END;
	last->next = new;
	return (first);
}

void	middle_child(t_command *cmd, int n_cmd, int fdp[2][2], t_env *envp)
{
	int		next_pipe;
	int		prev_pipe;

	prev_pipe = (n_cmd + 1) % 2;
	next_pipe = n_cmd % 2;
	close(fdp[next_pipe][READ_END]); //cerramos el read de la pipe que aun no esta usandose porque solo vamos a escribir en ella.
	dup2(fdp[prev_pipe][READ_END], STDIN_FILENO); // STDIN ahora es la lectura de la pipe anterior
	close(fdp[prev_pipe][READ_END]); // cerramos la lectura porque ya la tiene STDIN 
	dup2(fdp[next_pipe][WRITE_END], STDOUT_FILENO); // STDOUT ahora es la escritura de la pipe siguiente
	close(fdp[next_pipe][READ_END]); // cerramos la escritura porque ya la tiene STDOUT 
	execution(cmd, envp, 1); //y finalmente ejecutamos.TENGO QUE MODIFICAR AQUI
	exit (0);
}

void	last_child(t_command *cmd, int fdp[2], t_env *envp)
{
	dup2(fdp[READ_END], STDIN_FILENO); //la entrada estandar ahora es el pipe de entrada.
	close(fdp[READ_END]); //lo cerramos porque STDIN ya lo tiene.
	execution(cmd, envp, 1); //y finalmente ejecutamos el comando.TENGO QUE MODIFICAR AQUI
	exit (0);
}

void	first_child(t_command *cmd, int fdp[2], t_env *envp)
//void	first_child(t_px_args *args, int fdp[2], int fd_ph)
{
	close(fdp[READ_END]); // cierro read porque yo solo voy a escribir.
	dup2(fdp[WRITE_END], STDOUT_FILENO); //en la salida estandar le decimos que escriba en la parte write del pipe pasado.
	close(fdp[WRITE_END]); //cerramos porque ya esta en STDOUT con el dup
	execution(cmd, envp, 1); //Y finalmente ejecutamos. TENGO QUE MODIFICAR AQUI
	exit (0);
}

void	man_child(t_command *cmd, int n_cmd, int fdp[2][2], pid_t pid, t_env *e)
//void	childs_management(t_px_args *args, int fdp[2][2], pid_t pid, int fd_ph)
{
	if (pid == -1)
		exit(-1);
	else if (pid == 0) //el proceso hijo
	{
		if (n_cmd == 0)
			first_child(cmd, fdp[(n_cmd) % 2], e); //fd_ph solo si es el primero.
		else if (!cmd->next)
			last_child(cmd, fdp[((n_cmd) + 1) % 2], e); // +1 es el anterior (izq). CREAR FUNCION QUE CON EL N_CMD DEVUELVA PUNTERO A ESE COMANDO
		else
			middle_child(cmd, n_cmd, fdp, e); // al ser intermedio le paso los dos (fdp completo.)
	}
	else if (pid > 0) //el proceso padre
	{ //Aqui siempre actuamos sobre el ya creado y usado. Ya sabemos lo que va a hacer el siguiente con él.
		if (n_cmd == 0) //si es el primer comando cerramos la escritura
			close(fdp[(n_cmd) % 2][WRITE_END]); //porque el siguiente hijo de esta pipe solo le queda leer.
		else if (!cmd->next) //si es el ultimo comando cerramos la lectura
			close(fdp[(n_cmd + 1) % 2][READ_END]); // porque ya no vendrá ningun hijo más y asi queda cerrado todo tambien en el padre.
		else //Si es intermedia
		{
			close(fdp[(n_cmd) % 2][WRITE_END]); //cerramos la escritura porque el hijo que va a escribir ya la ha recibido abierta y el siguiente hijo de ella solo va a leer.
			close(fdp[(n_cmd + 1) % 2][READ_END]); //cerramos lectura de la anterior porque igualmente el hijo que va a ller ya la ha recibido abierta y asi el padre deja su copia totalmente cerrada ya.
		}
	}
}

int	exe_pipes(t_mt *node, t_env *envp)
{
	t_command	*lst_cmd;
	t_command	*first;
	int			fd_pipe[2][2];
	pid_t		pid;
	int			num_cmd;

	lst_cmd = lst_pipe_commands(node, envp);
	first = lst_cmd;
	num_cmd = 0; //para saber que cmd estoy ejecutando
	while (lst_cmd)
	{
		if (lst_cmd->next)
			if (pipe(fd_pipe[num_cmd % 2]) == -1)
				exit(-1);
		pid = fork();
		man_child(lst_cmd, num_cmd, fd_pipe, pid, envp);
		lst_cmd = lst_cmd->next;
		num_cmd++;
	}
	free_cmd_list(first);
	wait_for_children(num_cmd);
	// int			pipefd[2];          // FDs del pipe actual
	// int			prev_fd = -1;       // FD del pipe anterior
	// pid_t		pid;
	// t_command	*lst_cmd;
	// t_mt		current;

	// prev_fd = -1;
	// current = list;   // Iterador sobre los nodos de la lista
	// while (current)
	// {
	// 	// Crea un pipe si no es el último comando
	// 	if (current->next)
	// 	{
	// 		if (pipe(pipefd) == -1)
	// 		{
	// 			perror("pipe");
	// 			return (-1);
	// 		}
	// 	}

	// 	// Crea un proceso hijo para el comando actual
	// 	pid = fork();
	// 	if (pid == -1)
	// 	{
	// 		perror("fork");
	// 		return (-1);
	// 	}

	// 	if (pid == 0)
	// 	{
	// 		// Proceso hijo
	// 		if (prev_fd != -1)
	// 		{
	// 			dup2(prev_fd, STDIN_FILENO); // Lee del pipe anterior
	// 			close(prev_fd);
	// 		}
	// 		if (current->next)
	// 		{
	// 			dup2(pipefd[1], STDOUT_FILENO); // Escribe al pipe actual
	// 			close(pipefd[1]);
	// 			close(pipefd[0]);
	// 		}
	// 		exit(exe(current, env)); // Ejecuta el comando actual
	// 	}

	// 	// Proceso padre
	// 	if (prev_fd != -1)
	// 		close(prev_fd); // Cierra el pipe anterior

	// 	if (current->next)
	// 	{
	// 		close(pipefd[1]); // Cierra el extremo de escritura del pipe actual
	// 		prev_fd = pipefd[0]; // Mantén el extremo de lectura para el próximo comando
	// 	}

	// 	current = current->next; // Avanza al siguiente nodo
	// }

	// // Espera a todos los procesos hijos
	// while (wait(NULL) > 0)
	// 	;
	 return (1);
}
