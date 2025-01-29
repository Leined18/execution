/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:27:24 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/29 17:53:11 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void execute_tree(t_mt *node, t_env *env)
{
	if (!node)
		return;
	if (!is_ope_or_red(node))
		process_command(node, env);
	else
		execute_pipe(node, env);
}
