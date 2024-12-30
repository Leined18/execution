/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/30 12:42:22 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int		env_builtin(t_command *cmd, t_env *envp)
{
	t_mt	*aux;

	(void)cmd;
	if (envp->mt_env != NULL)
	{
		aux = envp->mt_env;
		while (aux)
		{
			ft_printf("%s\n", (char *)(aux->data));
			aux = aux->vect.right;
		}
		return (0);
	}
	return (1);
}
