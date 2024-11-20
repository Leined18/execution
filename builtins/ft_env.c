/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/20 12:17:34 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_lst_data(t_mt *array)
{
	t_mt	*node;

	if (array)
	{
		node = array;
		while (node)
		{
			ft_printf("[%s]", (char *)(node->data));
			node = node->next;
			if (node)
				ft_printf("->");
			else
				ft_printf("\n");
		}
	}
}

void	env_builtin(t_mt **first)
{
	t_mt	*aux;

	if (first != NULL)
	{
		aux = *first;
		while (aux)
		{
			ft_printf("%s\n", (char *)(aux->data));
			aux = aux->next;
		}
	}
}
