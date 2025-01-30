/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:27:24 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/30 10:39:35 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void execute_tree(t_mt *node, t_env *env, int is_child)
{
	if (!node)
		return;
	if (!is_ope_or_red(node))
		process_command(node, env, is_child);
	else
		execute_pipe(node, env);
}
