/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/08 18:27:33 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	*expand_home(char *where, t_env *envp)
{
	char	*expanded;
	char	*cleaned;
	char	*home_value;
	size_t	len;

	cleaned = ft_strltrim(where, "~");
	if (!cleaned)
		return (NULL);
	len = get_len_env("HOME", envp->mt_env, 0);
	len += ft_strlen(cleaned);
	len += 1;
	expanded = ft_calloc(len, sizeof(char));
	if (!expanded)
		return (free(cleaned), NULL);
	home_value = ft_getenv_value("HOME", envp->mt_env);
	ft_strlcat(expanded, home_value, len);
	ft_strlcat(expanded, cleaned, len);
	return(free(cleaned), free(home_value), expanded);
}

char	*get_expanded_path(char *path, t_env *envp)
{
	char	*expanded;
	if (!path || ft_pmatch_str(path, "~", 1) == 0)
		expanded = ft_getenv_value("HOME", envp->mt_env);
	else if (ft_pmatch_str(path, "-", 1) == 0)
	{
		expanded = ft_getenv_value("OLDPWD", envp->mt_env);
		ft_printf("%s\n", expanded);
	}
	else
	{
		if (path && path[0] == '~' && path[1] == '/')
			expanded = expand_home(path, envp);
		else
			expanded = ft_strdup(path);
	}
	return (expanded);
}

int	cd_builtin(t_command *cmd, t_env *envp)
{
	char	*prev_path;
	char	*new_path;
	char	*path;

	path = NULL;
	if (cmd->args)
		path = cmd->args[1];
	prev_path = getcwd(NULL, 0);
	if (prev_path == NULL)
		return (perror("getcwd"), 1);
	new_path = get_expanded_path(path, envp);
	if (chdir(new_path) != 0)
		return (free(new_path), free(prev_path), perror("cd"), 1);
	free(new_path);
	new_path = getcwd(NULL, 0);
	ft_setenv("PWD", new_path, envp, 1);
	ft_setenv("OLDPWD", prev_path, envp, 1);
	return (free(prev_path), free(new_path), 0);
}
