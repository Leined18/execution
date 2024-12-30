/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:14 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/07 18:44:03 by mvidal-h         ###   ########.fr       */
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
			aux = aux->vect[RIGHT];
		}
		ft_printf("numero de entorno: %d\n", envp->num_env);
		return (0);
	}
	return (1);
}
