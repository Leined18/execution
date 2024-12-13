/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:30 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/13 17:13:23 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	unset_builtin(char **args, t_env *envp)
{
	int		i;
	t_mt	*del;
	t_mt	**list;
	int		*num;

	i = 1;
	while (args[i])
	{
		del = ft_mtsearch_list(envp->mt_env, args[i]);
		list = &envp->mt_env;
		num = &envp->num_env;
		if (!del)
		{
			del = ft_mtsearch_list(envp->mt_var, args[i]);
			list = &envp->mt_var;
			num = &envp->num_var;
		}
		if (del)
		{
			ft_mtdel_one(list, del);
			(*num)--;
		}
		i++; 
	}
	return (0);
}
