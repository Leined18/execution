/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmlst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:22:21 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/30 12:49:17 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_mtdel_one(t_mt **first, t_mt *node) // PONER EN memtrack/src/list
{
	if (!node)
		return ;
	if (node->vect.left)
		node->vect.left->vect.right = node->vect.right;
	else
		*first = node->vect.right;
	if (node->vect.right)
		node->vect.right->vect.left = node->vect.left;
	ft_mtdelete(&node);
}

t_mt	*ft_mtpop_one(t_mt **first, char *find) // PONER EN memtrack/src/list
{
	t_mt *extract;
	extract = ft_mtsearch_key(*first, find);
	if (!extract)
		return (NULL);
	if (extract->vect.left)
		extract->vect.left->vect.right = extract->vect.right;
	else
		*first = extract->vect.right;
	if (extract->vect.right)
		extract->vect.right->vect.left = extract->vect.left;
	extract->vect.right = NULL;
	extract->vect.left = NULL;
	return (extract);
}

void	print_lst_data(t_mt *array)
{
	t_mt *node;

	if (array)
	{
		node = array;
		while (node)
		{
			ft_printf("[%s]", (char *)(node->data));
			node = node->vect.right;
			if (node)
				ft_printf("->");
			else
				ft_printf("\n");
		}
	}
}