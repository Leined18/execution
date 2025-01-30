/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:27:24 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/30 15:54:29 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	execute_tree(t_mt *node, t_env *env, int is_child)
{
	if (!node)
		return (1);
	if (!is_ope_or_red(node))
	{
		if (ft_strchr(node->key, '=')) //BORRAR ft_mtcheck_state(node, ASSIGNMENT) == 0 (cuando se arregle).
			return (ft_assignation(node, env));
		else
			return (process_command(node, env, is_child));
	}
	else
		return (execute_pipe(node, env));
}
