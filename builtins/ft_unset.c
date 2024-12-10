/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:30 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/10 17:01:32 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_mtdel_one(t_mt **first, t_mt *node) //PONER EN memtrack/src/list
{
	if (!node)
		return ;
    if (node->left)
    	node->left->right = node->right;
	else
		*first = node->right;
	if (node->right)
		node->right->left = node->left;
	ft_mtfree(node);
}

int	unset_builtin(char **args, t_env *envp)
{
	int		i;
	t_mt	*del;

	i = 1;

	while (args[i])
	{
		del = ft_mtsearch_list(envp->mt_env, args[i++]);
		if (del)	
			ft_mtdel_one(&envp->mt_env, del);
	}
	return (0);
}