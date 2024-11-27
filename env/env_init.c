/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/27 18:07:32 by mvidal-h         ###   ########.fr       */
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
int	copy_envp(t_env **environ, char **envp)
{
	int		counter;
	char	*node_content;

	counter = 0;
	*environ = chaosmatrix(1, sizeof(t_env), 0);
	if (!(*environ))
		return (0);
	while (envp[counter])
		counter++;
	(*environ)->num_env = counter;
	(*environ)->mt_env = NULL;
	counter = 0;
	while (counter < (*environ)->num_env)
	{
		node_content = ft_strmtdup(envp[counter]);
		if (!node_content)
			return (0);
		ft_mtpush_data_back(&(*environ)->mt_env, node_content);
		counter++;
	}
	(*environ)->path = split_path_env(envp);
	init_builtins((*environ)->builtins);
	return (1);
}
