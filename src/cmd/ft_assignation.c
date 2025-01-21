/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assignation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:36:22 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/21 19:48:12 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "cmd.h"
#include "exe_utils.h"
#include "builtin.h"

//int	check_all_assignaments(t_command *cmd)//Pensar en como gestionar esto, si creando los comandos con un puntero a next, o, si no, chequearlo fuera (en main) y luego asignar uno a uno.

int	check_all_assignations(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
			return(i);
		i++;
	}
	return (0);
}

int ft_assignation(t_mt *node, t_env *envp)
{
	char		**split_arg;
	char		*value;
	int			result;
	t_command 	*cmd;
	int			i;

	if (!node || !envp)
		return (-1);
	cmd = create_command(node, envp);
	i = 0;
	result = check_all_assignations(cmd->args);
	if (result == 0)
	{
		while (cmd->args[i])
		{
			value = ft_strchr(cmd->args[i], '=');
			value += 1;
			value = ft_expand(value, node->values.state, envp);
			split_arg = ft_split(cmd->args[i], '=');
			ft_setenv(split_arg[0], value, envp, 1);
			generate_path(split_arg[0], &envp);
			free(value);
			free_array2d(split_arg);
			i++;
		}
	}
	else
		ft_printf("assignation: '%s' is not found.\n", cmd->args[result]);
	node->values.state = END;
	return (free_command(cmd), result);
}
