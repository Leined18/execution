/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:18 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/20 18:50:13 by mvidal-h         ###   ########.fr       */
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
int	exe_in_child(t_command *cmd,  char **array_envp)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0) // hijo
		exec_command(cmd, array_envp);
	else if (pid < 0)
		return (perror("FORK failed"), 1);
	waitpid(pid, NULL, 0);
	free_array2d(array_envp);
	return (0);
}

int	execution(t_command *cmd, t_env *envp, int is_child)
{
	int			i;
	t_builtin	*bltn;
	char		**array_envp;

	i = 0;
	bltn = envp->builtins;
	while (bltn[i].name)
	{
		if (ft_pmatch_str(cmd->command, bltn[i].name,
				ft_strlen(bltn[i].name)) == 0)
			return (bltn[i].func(cmd, envp));
		i++;
	}
	array_envp = mtconvert_array2d(envp->mt_env);
	if (!is_child)
	{
		exe_in_child(cmd, array_envp);
		return (0);
	}
	exec_command(cmd, array_envp);
	return (0);
}
