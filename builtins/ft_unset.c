/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:30 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/10 14:59:02 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	unset_builtin(char **args, t_env *envp)
{
	int		i;
	t_mt	*del;

	i = 1;

	while (args[i])
	{
		del = ft_mtsearch_list(envp->mt_env, args[i++]);
		if (del)
			ft_printf("encontrado %s\n", del->data);		
	}
	return (0);
}