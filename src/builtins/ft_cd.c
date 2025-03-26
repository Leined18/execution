/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/26 15:26:38 by mvidal-h         ###   ########.fr       */
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
	return (free(cleaned), free(home_value), expanded);
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

void	create_dir_history(char *dir, t_env *envp)
{
	t_mt	*new;
	char	**dir_split;
	char	*elem_dir;
	int		i;

	if (envp->dir_history)
		ft_mtclear(&envp->dir_history);
	i = 0;
	dir_split = ft_split(dir, '/');
	if (!dir_split)
		return ;
	while (dir_split[i])
	{
		elem_dir = ft_strdup(dir_split[i++]);
		new = ft_mtnew(elem_dir, elem_dir, STRING);
		if (!new)
			break ;
		ft_mtaddlast(&envp->dir_history, new, RIGHT);
	}
	(free_array2d(dir_split), free(dir));
}


int	cd_builtin(t_command *cmd, t_env *envp)
{
	char	*prev_path;
	char	*new_path;
	char	*path;

	path = NULL;
	if (cmd->args.names)
		path = cmd->args.names[1];
	prev_path = getcwd(NULL, 0);
	if (prev_path == NULL)
		return (perror("getcwd"), envp->last_status = 1, 1);
	new_path = get_expanded_path(path, envp);
	if (chdir(new_path) != 0)
	{
		(free(new_path), free(prev_path));
		return (perror("cd"), envp->last_status = 1, 1);
	}
	else
	{
		create_dir_history(getcwd(NULL, 0), envp);
		print_lst_data(envp->dir_history);
	}
	free(new_path);
	new_path = getcwd(NULL, 0);
	ft_setenv("PWD", new_path, envp, 1);
	ft_setenv("OLDPWD", prev_path, envp, 1);
	return (free(prev_path), free(new_path), envp->last_status = 0, 0);
}
