/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/11 14:22:51 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

void	env_builtin(t_list **first)
{
	t_list	*aux;

	if (first != NULL)
	{
		ft_printf("ENNNNNNNNN\n");
		aux = *first;
		ft_printf("ENNNNNNNNNqqqqqqqqq\n");
		while (aux)
		{
			ft_printf("%s\n", *(char **)(aux->content));
			//ft_printf("%s\n", (char *)*(node_env->content));
			aux = aux->next;
		}
	}
	ft_printf("final----");
}
