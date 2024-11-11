/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/11 17:33:25 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"

// Finds the line that starts with "PATH=" in env, and, if exists
// creates and array splitting the line with ":" and returns it.
char	**split_path_env(char *env[])
{
	int		i;
	char	*path;
	char	**path_array;

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
		path_array = ft_split(path, ':');
		i = 0;
	}
	return (path_array);
}

// Genera una copia del entorno en una variable de tipo t_env (mirar minishell.h)
int	copy_envp(t_env **environ, char **envp)
{
	int		counter;
	t_list	*node_env;
	char	*node_content;

	counter = 0;
	*environ = malloc(sizeof(t_env));
	if (!(*environ))
		return (0);
	while (envp[counter])
		counter++;
	(*environ)->num_env = counter;
	(*environ)->lst_env = NULL;
	counter = 0;
	while (counter < (*environ)->num_env)
	{
		node_content = ft_strdup(envp[counter]);
		if (!node_content)
			return (0);
		node_env = ft_lstnew((void *)node_content);
		if (!node_env)
			return (free(node_content), 0);
		ft_lstadd_back(&(*environ)->lst_env, node_env);
		counter++;
	}
	(*environ)->path = split_path_env(envp);
	return (1);
}
