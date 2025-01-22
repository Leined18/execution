/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:18 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/22 17:41:10 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_utils.h"
#include "types.h"
#include <sys/wait.h>
#include <unistd.h>

int update_last_status(int status)
{
	if (WIFEXITED(status)) // El proceso terminó normalmente
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status)) // El proceso fue terminado por una señal
		return (128 + WTERMSIG(status)); // Suma 128 al número de la señal
	else
		return (1); // Caso genérico de error inesperado
}

void	exec_command(t_command *cmd, char **env)
{
	if (cmd->cmd_path)
	{
		if (access(cmd->cmd_path, X_OK) == 0)
		{
			execve(cmd->cmd_path, cmd->args, env);
			perror("execve failed.");
		}
		else
			perror("Command not accessible.");
	}
	else
		perror("Command not found.");
	free_array2d(env);
	exit(EXIT_FAILURE);
}

int	exe_in_child(t_command *cmd, t_env *envp, char **array_envp)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == 0) // hijo
		exec_command(cmd, array_envp);
	else if (pid < 0)
		return (perror("FORK failed"), envp->last_status = 1, 1);
	waitpid(pid, &status, 0);
	envp->last_status = update_last_status(status);
	free_array2d(array_envp);
	return (0);
}

int	execution(t_command *cmd, t_env *envp, int is_child)
{
	int			i;
	t_builtin	*bltn;
	char		**array_envp;
	int			status;

	i = 0;
	bltn = envp->builtins;
	while (bltn[i].name)
	{
		if (ft_pmatch_str(cmd->command, bltn[i].name,
				ft_strlen(bltn[i].name)) == 0)
		{
			status = bltn[i].func(cmd, envp);
			if (is_child)
				exit(status);
			return (status);
		}
		i++;
	}
	array_envp = mtconvert_array2d(envp->mt_env);
	if (!is_child)
		return (exe_in_child(cmd, envp, array_envp));
	exec_command(cmd, array_envp);
	return (0);
}
