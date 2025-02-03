/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:50 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/03 18:16:23 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	redirect_output(t_mt *node, int open_mode)
{
	int fd;
	
	fd = secure_open(node->aux->key, open_mode);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error("Error redirigiendo la salida estándar\n", 0);
	close(fd);
}
