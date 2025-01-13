/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:18 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/13 11:05:39 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_utils.h"
#include "types.h"
#include <sys/wait.h>
#include <unistd.h>

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
	exit(1);
}

int	execution(t_command *cmd, t_env *envp)
{
	int			i;
	t_builtin	*bltn;
	char		**array_envp;
	pid_t		pid;
	int			status;

	i = 0;
	bltn = envp->builtins;
	while (bltn[i].name)
	{
		if (ft_pmatch_str(cmd->command, bltn[i].name,
				ft_strlen(bltn[i].name)) == 0)
			return (bltn[i].func(cmd, envp));
		i++;
	}
	pid = fork();
	if (pid == 0) // hijo
	{
		array_envp = mtconvert_array2d(envp->mt_env);
		exec_command(cmd, array_envp);
	}
	else if (pid < 0)
		return (perror("FORK failed"), 1);
	waitpid(pid, &status, 0);
	return (0);
}
