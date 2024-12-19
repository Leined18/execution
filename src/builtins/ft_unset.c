/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:30 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/19 16:42:23 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	unset_builtin(t_command *cmd, t_env *envp)
{
	int		i;
	t_mt	*del;
	t_mt	**list;
	int		*num;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		del = ft_mtsearch_key(envp->mt_env, cmd->args[i]);
		list = &envp->mt_env;
		num = &envp->num_env;
		if (!del)
		{
			del = ft_mtsearch_key(envp->mt_var, cmd->args[i]);
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
