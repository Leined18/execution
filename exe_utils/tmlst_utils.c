/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmlst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:22:21 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/18 11:03:38 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_mtdel_one(t_mt **first, t_mt *node) //PONER EN memtrack/src/list
{
	if (!node)
		return ;
	if (node->left)
		node->left->right = node->right;
	else
		*first = node->right;
	if (node->right)
		node->right->left = node->left;
	ft_mtfree(node);
}

t_mt	*ft_mtpop_one(t_mt **first, char* find) //PONER EN memtrack/src/list
{
	t_mt	*extract;
	extract = ft_mtsearch_key(*first, find);
	if (!extract)
		return (NULL);
	if (extract->left)
		extract->left->right = extract->right;
	else
		*first = extract->right;
	if (extract->right)
		extract->right->left = extract->left;
	extract->right = NULL;
	extract->left = NULL;
	return (extract);
}

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