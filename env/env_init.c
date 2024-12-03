/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/03 12:44:01 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// Finds the line that starts with "PATH=" in env, and, if exists
// creates and array splitting the line with ":" and returns it.
t_mt	*split_path_env(char *env[])
{
	int		i;
	char	*path;
	t_mt	*path_array;

	i = 0;
	path = NULL;
	path_array = NULL;
	if (!env)
		return (NULL);
	while (!path && env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (path)
	{
		path += 5;
		path_array = ft_splitmt(path, ':');
		i = 0;
	}
	return (path_array);
}

// Genera una copia del entorno en una variable de tipo t_env
t_env	*copy_envp(char **envp)
{
	int		counter;
	char	*node_content;
	t_env	*environ;

	counter = 0;
	environ = ft_calloc(1, sizeof(t_env));
	if (!(environ))
		return (NULL);
	while (envp[counter])
		counter++;
	environ->num_env = counter;
	environ->mt_env = NULL;
	counter = 0;
	while (counter < environ->num_env)
	{
		node_content = ft_strdup(envp[counter]);
		if (!node_content)
			return (NULL);
		ft_mtpush_data_back(&environ->mt_env, node_content, node_content,
			STRING);
		counter++;
	}
	environ->path = split_path_env(envp);
	init_builtins(environ->builtins);
	return (environ);
}
