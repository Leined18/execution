/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:27:24 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/30 21:02:44 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	endizide_nodes(t_mt *node)
{
	if (!node || node->values.state == END)
		return (0);
	node->values.state = END;
	endizide_nodes(node->vect[LEFT]);
	endizide_nodes(node->vect[RIGHT]);
	return (0);
}

int	execute_tree(t_mt *node, t_env *env, int is_child)
{
	if (!node)
		return (1);
	if (node->values.state != END)
	{
		if (!is_ope_or_red(node))
		{
			if (ft_strchr(node->key, '=')) //BORRAR ft_mtcheck_state(node, ASSIGNMENT) == 0 (cuando se arregle).
				ft_assignation(node, env);
			else
				process_command(node, env, is_child);
		}
		else
		{
			execute_pipe(node, env);
			if (!is_child)
				endizide_nodes(node);
		}
	}
	execute_tree(node->vect[LEFT], env, is_child);
	execute_tree(node->vect[RIGHT], env, is_child);
	return (0);
}
