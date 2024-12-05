/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmlst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:22:21 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/05 11:22:43 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	print_lst_data(t_mt *array)
{
	t_mt	*node;

	if (array)
	{
		node = array;
		while (node)
		{
			ft_printf("[%s]", (char *)(node->data));
			node = node->right;
			if (node)
				ft_printf("->");
			else
				ft_printf("\n");
		}
	}
}