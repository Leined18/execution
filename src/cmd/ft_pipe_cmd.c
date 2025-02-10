/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:01 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/10 11:00:07 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int update_last_status(int status)
{
	if (WIFEXITED(status)) // El proceso terminó normalmente
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status)) // El proceso fue terminado por una señal
		return (128 + WTERMSIG(status)); // Suma 128 al número de la señal
	else
		return (1); // Caso genérico de error inesperado
}

//Makes father process waiting for the children to ensure that all of them 
//finish correctly and avoid zombies process.
int	process_father(int pfd[2], int num_children, t_env *env)
{
	int	i;
	int	status;
	int last_exit_status;

	close(pfd[0]);
	close(pfd[1]);
	i = 0;
	while (i < num_children)
	{
		if (wait(&status) == -1)
			return(perror("wait"), env->last_status = 1, 1);
		last_exit_status = update_last_status(status);
		i++;
	}
	env->last_status = last_exit_status;
	return (0);
}

void	process_left_child(int pfd[2], t_mt *node, t_env *env)
{
	close(pfd[0]);							// Cierra la lectura del pipe
	dup2(pfd[1], STDOUT_FILENO);			// Redirige salida al pipe
	close(pfd[1]);							// Cierra descriptor duplicado
	ft_execute_tree(node->vect[LEFT], env, 1);	// Ejecuta el nodo izquierdo
	exit(0);
}

void	process_right_child(int pfd[2], t_mt *node, t_env *env)
{
	close(pfd[1]);               // Cierra la escritura del pipe
	dup2(pfd[0], STDIN_FILENO);   // Redirige entrada desde el pipe
	close(pfd[0]);               // Cierra descriptor duplicado
	ft_execute_tree(node->vect[RIGHT], env, 1);  // Ejecuta el nodo derecho
	exit(0);
}

int execute_pipe(t_mt *node, t_env *env)
{
	int		pfd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	
	if (pipe(pfd) == -1) {
		perror("pipe");
		exit(1);
	}
	pid_left = fork();
	if (pid_left == -1) {
		perror("fork");
		exit(1);
	}
	if (pid_left == 0)
		process_left_child(pfd, node, env);

	pid_right = fork();
	if (pid_right == -1) {
		perror("fork");
		exit(1);
	}
	if (pid_right == 0)
		process_right_child(pfd, node, env);
	process_father(pfd, 2, env);
	return (0);
}
