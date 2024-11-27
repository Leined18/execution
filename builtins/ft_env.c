/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/27 17:21:38 by mvidal-h         ###   ########.fr       */
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
			node = node->next;
			if (node)
				ft_printf("->");
			else
				ft_printf("\n");
		}
	}
}

int		env_builtin(char **args, t_env *envp)
{
	t_mt	*aux;

	(void)args;
	if (envp->mt_env != NULL)
	{
		aux = envp->mt_env;
		while (aux)
		{
			ft_printf("%s\n", (char *)(aux->data));
			aux = aux->next;
		}
		return (0);
	}
	return (1);
}
