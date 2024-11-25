/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/25 15:13:35 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*generate_relative_path(char *path, char *add)
{
	char	*new;
	size_t	len;
	
	if (path && add)
	{
		len = ft_strlen(path) + ft_strlen(add) + 2;
		new = ft_calloc(len, sizeof(char));
		ft_strlcat(new, path, len);
		ft_strlcat(new, "/", len);
		ft_strlcat(new, add, len);
		return (new);
	}
	return (NULL);
}

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
	else if (is_relative(path))
		new_path = generate_relative_path(prev_path, path);
	else if (new_path == NULL)
		new_path = ft_strdup(path);
	ft_printf("new_path = %s\n", new_path);
	if (chdir(new_path) != 0)
		return (free(prev_path), free(new_path), perror("cd"), 0);
	ft_setenv("PWD", new_path, envp->mt_env);
	ft_setenv("OLDPWD", prev_path, envp->mt_env);
	return (free(prev_path), free(new_path), 0);
}
