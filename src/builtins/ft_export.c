/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:53:25 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/20 17:17:32 by mvidal-h         ###   ########.fr       */
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

void	generate_path(char *var, t_env **envp)
{
	char	**array_envp;
	
	if (ft_pmatch_str(var, "PATH", 4) == 0) //Quizas mejora buscando si se ha modificado.
	{
		if ((*envp)->path)
		{
			free_array2d((*envp)->path);
			(*envp)->path = NULL;
		}
		array_envp = mtconvert_array2d((*envp)->mt_env);
		(*envp)->path = split_path_env(array_envp);
		free_array2d(array_envp);
	}
}


int		export_builtin(t_command *cmd, t_env *envp)
{
	int		i;
	char	**split_arg;

	i = 1;
	if (!cmd->args[i])
		ft_print_export(envp->mt_env);
	else
	{
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '='))
			{
				split_arg = ft_split(cmd->args[i], '=');
				ft_setenv(split_arg[0], split_arg[1], envp, 1);
				if (ft_mtmigrate_one(&envp->mt_var, &envp->mt_env, split_arg[0]) == 0)
					envp->num_var--;
				generate_path(split_arg[0], &envp);
				free_array2d(split_arg);
			}
			else if (ft_mtmigrate_one(&envp->mt_var, &envp->mt_env, cmd->args[i]) == 0)
				envp->num_var--;
			i++;
		}
	}
	return (0);
}
