/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:18 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/29 20:10:31 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	execute_command(t_command *cmd, char **env)
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
	return ;
}

int	select_command(t_command *cmd, t_env *envp)
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
			return (status);
		}
		i++;
	}
	array_envp = mtconvert_array2d(envp->mt_env);
	execute_command(cmd, array_envp); //LO DEBE EJECUTAR UN HIJO (TENGO QUE ARREGLARLO)
	return (0);
}

int	process_command(t_mt *node, t_env *env) // to build, execute commands
{
	t_command *cmd;

	if (!node || !env)
		return (0);
	cmd = create_command(node, env);
	 print_command(cmd);
	if (ft_pmatch_str(cmd->command, "path", 4) == 0)
		print_array2d(env->path);
	else if (ft_pmatch_str(cmd->command, "vars", 4) == 0)
		print_lst_data(env->mt_var);
	else
		select_command(cmd, env);
	node->values.state = END;
	free_command(cmd);
	return (1);
}

