/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:38 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/03 18:16:28 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	redirect_input(t_mt *node, int open_mode)
{
	int	fd;
	
	fd = secure_open(node->aux->key, open_mode);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error("Error redirigiendo la entrada estándar\n", 0);
	close(fd);
}
