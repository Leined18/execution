/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/11 15:04:45 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "env.h"

// Finds the line that starts with "PATH=" in env, and, if exists
// creates and array splitting the line with ":" and returns it.
char	**split_path_env(char *env[])
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
int	copy_envp(t_env **environ, char **envp, t_list **list)
{
	int		counter;
	t_list	*node_env;
	char	*node_content;

	//(void)list;
	counter = 0;
	(*environ) = malloc(sizeof(t_env));
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
		ft_hold_mem(1, list, &node_content);
		node_env = ft_lstnew((void **)&node_content); /////
		if (!node_env)
			return (0);
		ft_hold_mem(1, list, &node_env);
		ft_lstadd_back(&(*environ)->lst_env, node_env);
		ft_printf("Contenido del 1 nodo: %s\n", *(char **)(*environ)->lst_env->content);
		counter++;
	}
	ft_printf("Contenido del primer nodo: %s\n", *(char **)(*environ)->lst_env->content);
	ft_printf("Contenido del segundo nodo: %s\n", *(char **)(*environ)->lst_env->next->content);
	ft_printf("Contenido del tercer nodo: %s\n", *(char **)(*environ)->lst_env->next->next->content);
	(*environ)->path = split_path_env(envp);
	ft_hold_mem(2, list, &(*environ), &(*environ)->path);
	ft_lstadd_2d(list, (*environ)->path);
	return (1);
}
