/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:01 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/17 14:16:26 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	free_cmd_list(t_command *lst)
{
	t_command	*next_node;
	ft_printf("freeing list of commands...\n");
	while (lst)
	{
		next_node = lst->next;
		free_command(lst);
		lst = next_node;
	}
	ft_printf("Done!\n");
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

t_command	*lst_pipe_commands(t_mt *node, t_env *envp)
{
	t_mt		*select;
	t_mt		*prev;
	t_command	*first;
	t_command	*last;
	t_command	*new;

	select = node;
	first = NULL;
	last = NULL;
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
	last = new;
	return (first);
}


int	exe_pipes(t_mt *node, t_env *envp)
{
	t_command	*lst;

	lst = lst_pipe_commands(node, envp);
	print_cmd_list(lst);
	free_cmd_list(lst);
	// int		pipefd[2];
	// pid_t	pid1;
	// pid_t	pid2;

	// if (!cmd1 || !cmd2)
	// 	return ;
	// if (pipe(pipefd) == -1)
	// 	ft_error("Error al crear el pipe\n", 1);
	// pid1 = fork();
	// if (pid1 == -1)
	// 	ft_error("Error al hacer fork\n", 1);
	// if (pid1 == 0)
	// 	create_child(cmd1, pipefd, 1);
	// pid2 = fork();
	// if (pid2 == -1)
	// 	ft_error("Error al hacer fork\n", 1);
	// if (pid2 == 0)
	// 	create_child(cmd2, pipefd, 2);
	// handle_parent(pipefd, pid1, pid2);

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
