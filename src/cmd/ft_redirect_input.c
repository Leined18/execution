/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:38 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/26 11:49:26 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	redirect_input(t_mt *node, int open_mode, t_env *env)
{
	int	fd;

	fd = secure_open(node->aux->key, open_mode);
	if (fd == -1)
	{
		endizide_nodes(node->vect[RIGHT]);
		return (env->last_status = 1, 1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_error("Error redirigiendo la entrada estándar\n", 0);
		return (env->last_status = 1, 1);
	}
	env->redirect.is_red_in = 1;
	close(fd);
	return (env->last_status = 0, 0);
}
