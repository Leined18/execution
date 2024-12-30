/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmlst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:22:21 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/07 18:46:58 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

size_t	ft_mtcount_node(t_mt *lst)
{
	size_t	count;
	t_mt	*aux;

	if (!lst)
		return (0);
	count = 1;
	aux = lst;
	while (aux->vect[RIGHT])
	{
		count++;
		aux = aux->vect[RIGHT];
	}
	return (count);
}	

void	ft_mtdel_one(t_mt **first, t_mt *node) //PONER EN memtrack/src/list
{
	if (!node)
		return ;
	if (node->vect[LEFT])
		node->vect[LEFT]->vect[RIGHT] = node->vect[RIGHT];
	else
		*first = node->vect[RIGHT];
	if (node->vect[RIGHT])
		node->vect[RIGHT]->vect[LEFT] = node->vect[LEFT];
	ft_mtdelete(&node);
}

t_mt	*ft_mtpop_one(t_mt **first, char *find) // PONER EN memtrack/src/list
{
	t_mt	*extract;

	extract = ft_mtsearch_key(*first, find);
	if (!extract)
		return (NULL);
	if (extract->vect[LEFT])
		extract->vect[LEFT]->vect[RIGHT] = extract->vect[RIGHT];
	else
		*first = extract->vect[RIGHT];
	if (extract->vect[RIGHT])
		extract->vect[RIGHT]->vect[LEFT] = extract->vect[LEFT];
	extract->vect[RIGHT] = NULL;
	extract->vect[LEFT] = NULL;
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
			node = node->vect[RIGHT];
			if (node)
				ft_printf("->");
			else
				ft_printf("\n");
		}
	}
}