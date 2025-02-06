/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:50 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/06 16:12:25 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	redirect_output(t_mt *node, int open_mode, t_env *env)
{
	int fd;
	
	fd = secure_open(node->aux->key, open_mode);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		{
		ft_error("Error redirigiendo la salida estándar\n", 0);
		return (-1);
	}
	env->redirect.is_red_out = 1;
	close(fd);
	return (0);
}
