/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:48:38 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/27 08:49:05 by danpalac         ###   ########.fr       */
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
