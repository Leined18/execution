/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/27 19:16:11 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	cd_builtin(char **args, t_env *envp)
{
	char	*prev_path;
	char	*new_path;
	char	*path;

	path = args[1];
	prev_path = getcwd(NULL, 0);
	if (prev_path == NULL)
		return (perror("getcwd"), 1);
	new_path = NULL;
	if (!path || ft_pmatch_str(path, "~", 1) == 0)
		new_path = ft_getenv_value("HOME", envp->mt_env);
	else if (ft_pmatch_str(path, "-", 1) == 0)
	{
		new_path = ft_getenv_value("OLDPWD", envp->mt_env);
		ft_printf("%s\n", new_path);
	}
	else if (new_path == NULL)
		new_path = path;
	if (chdir(new_path) != 0)
		return (free(prev_path), perror("cd"), 1);
	new_path = getcwd(NULL, 0);
	ft_setenv("PWD", new_path, envp->mt_env);
	ft_setenv("OLDPWD", prev_path, envp->mt_env);
	return (free(prev_path), free(new_path), 0);
}
