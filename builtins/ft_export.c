/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:25 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/13 17:43:14 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_print_export(t_mt *lst_exp)
{
	t_mt	*aux;
	char	**split_exp;

	if (lst_exp != NULL)
	{
		aux = lst_exp;
		while (aux)
		{
			split_exp = ft_split((char *)(aux->data), '=');
			ft_printf("declare -x %s=\"%s\"\n", split_exp[0], split_exp[1]);
			aux = aux->right;
			free_array2d(split_exp);
		}
	}
}

void	ft_mtmigrate_one(t_mt **src, t_mt **dest, char *migrate)
{
	t_mt	*mig_nod;

	mig_nod = ft_mtpop_one(src, migrate);
	ft_mtadd_back(dest, mig_nod);
}

int		export_builtin(char **args, t_env *envp)
{
	if (!args[1])
		ft_print_export(envp->mt_env);
	else if (ft_strchr(args[1], '='))
	{
		return (1);
	}
	else
	{
		ft_mtmigrate_one(&envp->mt_var, &envp->mt_env, args[1]);
		envp->num_var--;
	}
	return (0);
}
