/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assignation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:36:22 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/06 12:18:29 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "cmd.h"
#include "exe_utils.h"
#include "builtin.h"

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

int	create_assignations(t_command *cmd, t_mt *node, t_env *envp)
{
	char	**split_arg;
	char	*value;
	int		i;

	if (!cmd || !node || !envp)
		return (1);
	i = 0;
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
	return (0);
}

int ft_assignation(t_mt *node, t_env *envp)
{
	int			result;
	t_command 	*cmd;

	if (!node || !envp)
		return (-1);
	cmd = create_command(node, envp);
	result = check_all_assignations(cmd->args);
	if (result == 0)
		create_assignations(cmd, node, envp);
	else
		ft_printf("assignation: '%s' is not found.\n", cmd->args[result]);
	node->values.state = END;
	return (free_command(cmd), result);
}
