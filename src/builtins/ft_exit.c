/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:50:32 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/22 16:06:09 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	exit_builtin(t_command *cmd, t_env *envp)
{
	int exit_code;

	exit_code = 0;
	ft_printf("exit\n");
	if (cmd->args && cmd->args[1]) {
		if (!ft_isstrnum(cmd->args[1]))
		{
			ft_printf("exit: %s: numeric argument required\n", cmd->args[1]);
			exit_code = 2;
		}
		else if (cmd->args[2])
		{
			ft_printf("exit: too many arguments\n");
			return (envp->last_status = -1, -1);
		}
		else
			exit_code = ft_atoi(cmd->args[1]);
	}
	if (envp)
	{
		ft_env_free(envp);
		free_command(cmd);
		rl_clear_history();
	}
	exit(exit_code);
}
