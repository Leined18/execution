/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assignation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:36:22 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/13 12:52:05 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "cmd.h"
#include "exe_utils.h"
#include "builtin.h"

int	create_var(t_command *cmd, t_env *envp)
{
	char	**split_arg;
	char	*value;
	int		result;

	result = 1;
	if (array2d_len(cmd->args) == 1)
	{
		value = ft_strchr(cmd->args[0], '=');
		value += 1;
		split_arg = ft_split(cmd->args[0], '=');
		ft_setenv(split_arg[0], value, envp, 1);
		generate_path(split_arg[0], &envp);
		free_array2d(split_arg);
		result = 0;
	}
	else
		ft_printf("assignation: '%s' is not found.\n", cmd->args[1]);
	free_command(cmd);
	return (result);
}

//int	check_all_assignaments(t_command *cmd)//Pensar en como gestionar esto, si creando los comandos con un puntero a next, o, si no, chequearlo fuera (en main) y luego asignar uno a uno.

int ft_assignation(t_mt *node, t_env *env)
{
	t_command *cmd;

	if (!node || !env)
		return (0);
	cmd = create_command(node, env->path);
	return (create_var(cmd, env));
}