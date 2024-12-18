/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:25 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/16 12:51:42 by mvidal-h         ###   ########.fr       */
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

int	ft_mtmigrate_one(t_mt **src, t_mt **dest, char *migrate)
{
	t_mt	*mig_nod;

	mig_nod = ft_mtpop_one(src, migrate);
	if (mig_nod)
	{
		ft_mtadd_back(dest, mig_nod);
		return (0);
	}
	return (1);

}


int		export_builtin(char **args, t_env *envp)
{
	int		i;
	char	**split_arg;

	i = 1;
	if (!args[i])
		ft_print_export(envp->mt_env);
	else
	{
		while (args[i])
		{
			if (ft_strchr(args[i], '='))
			{
				split_arg = ft_split(args[i], '=');
				ft_setenv(split_arg[0], split_arg[1], envp, 1);
				if (ft_mtmigrate_one(&envp->mt_var, &envp->mt_env, split_arg[0]) == 0)
					envp->num_var--;
				free_array2d(split_arg);
			}
			else if (ft_mtmigrate_one(&envp->mt_var, &envp->mt_env, args[i]) == 0)
				envp->num_var--;
			i++;
		}
	}
	return (0);
}
