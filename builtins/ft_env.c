/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/09 15:38:54 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

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
			aux = aux->right;
		}
		ft_printf("\n");
		return (0);
	}
	return (1);
}
