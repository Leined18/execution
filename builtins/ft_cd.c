/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/26 18:41:28 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_builtin(char *path, t_env *envp)
{
	char	*prev_path;
	char	*new_path;

	prev_path = getcwd(NULL, 0);
	if (prev_path == NULL)
		return (perror("getcwd"), 0);
	new_path = NULL;
	if (!(*path) || (ft_strlen(path) == 1 && path[0] == '~'))
		new_path = ft_getenv_value("HOME", envp->mt_env);
	else if (ft_strlen(path) == 1 && path[0] == '-')
	{
		new_path = ft_getenv_value("OLDPWD", envp->mt_env);
		ft_printf("%s\n", new_path);
	}
	else if (new_path == NULL)
		new_path = path;
	if (chdir(new_path) != 0)
		return (free(prev_path), perror("cd"), 0);
	new_path = getcwd(NULL, 0);
	ft_setenv("PWD", new_path, envp->mt_env);
	ft_setenv("OLDPWD", prev_path, envp->mt_env);
	return (free(prev_path), free(new_path), 0);
}
