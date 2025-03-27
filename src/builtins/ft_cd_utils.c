/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:22:26 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/27 17:03:44 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	*create_complete_path(t_mt *dir_history)
{
	t_mt	*aux;
	char	*path;

	if (!dir_history)
		return (NULL);
	aux = dir_history;
	path = ft_strdup("/");
	while (aux)
	{
		path = ft_strjoin_free(&path, &(aux->key), 0);
		if (aux->vect[RIGHT])
			path = ft_straddc(path, '/');
		aux = aux->vect[RIGHT];
	}
	return (path);
}

t_mt	*create_prev_dir(char *dir)
{
	t_mt	*new;
	t_mt	*list;
	char	**dir_split;
	char	*elem_dir;
	int		i;

	list = NULL;
	i = 0;
	dir_split = ft_split(dir, '/');
	if (!dir_split)
		return (NULL);
	while (dir_split[i])
	{
		elem_dir = ft_strdup(dir_split[i++]);
		new = ft_mtnew(elem_dir, elem_dir, STRING);
		if (!new)
			break ;
		ft_mtaddlast(&list, new, RIGHT);
	}
	return (free_array2d(dir_split), list);
}

/*
Looks for the node where we will try to start moving back. It returns NULL
if the cd fail was in another "branch" from behind or it tries to go fordward.
If it returns a node, we will try to go from this directory to the previous one 
till we find an existing directory.
*/
t_mt	*find_node_start_moving(t_mt *cur_list, t_mt *prev_dir)
{
	t_mt	*aux;
	t_mt	*aux2;
	t_mt	*prev;

	aux = cur_list;
	aux2 = prev_dir;
	prev = NULL;
	while (aux && aux2)
	{
		if (ft_pmatch_str(aux->key, aux2->key, ft_strlen(aux2->key)) != 0)
			return (NULL);
		prev = aux2;
		aux = aux->vect[RIGHT];
		aux2 = aux2->vect[RIGHT];
	}
	if ((!aux && !aux2) || aux2)
		return (prev);
	if (aux)
		return (NULL);
	return (NULL);
}

void	delete_innecessary_right(t_mt *start)
{
	while (start->vect[RIGHT])
		ft_mtpoplast(&start, RIGHT);
}

int	move_valid_place(char **new_path, char **prev_path, t_env *env)
{
	t_mt	*cur_list;
	t_mt	*start;
	char	*cur_dir;

	ft_printf("BORRAR - entro en move_valid_place\n");
	if (!new_path)
		return (1);
	if (ft_pmatch_str(*new_path, "..", 2) == 0)
	{
		ft_printf("BORRAR - entro en ..\n");
		ft_mtpoplast(&(env->prev_dir), RIGHT);
		ft_mtpoplast(&(env->prev_dir), RIGHT);
		print_lst_data(env->prev_dir);//BORRAR
		free(*new_path);
		*new_path = create_complete_path(env->prev_dir);
		ft_printf("BORRAR - new_path: %s\n", *new_path);
	}
	cur_list = create_prev_dir(*new_path);
	start = find_node_start_moving(cur_list, env->prev_dir);
	ft_mtclear(&cur_list);
	if (!start)
	{
		(free(*new_path), free(*prev_path));
		return (perror("cd"), env->last_status = 1, 1);
	}
	else
	{
		delete_innecessary_right(start);
		while (env->prev_dir)
		{
			cur_dir = create_complete_path(env->prev_dir);
			ft_printf("BORRAR - cur_dir: %s\n", cur_dir);
			if (chdir(cur_dir) != 0)
			{
				ft_printf("no he podido cambiar de directorio. siguiente vuelta...\n");
				ft_mtpoplast(&env->prev_dir, RIGHT);
			}
			else
			{
				ft_printf("he podido cambiar de directorio\n");
				free(*new_path);
				*new_path = getcwd(NULL, 0);
				ft_setenv("PWD", *new_path, env, 1);
				ft_setenv("OLDPWD", *new_path, env, 1);
				delete_innecessary_right(env->prev_dir);
			}
			free(cur_dir);
		}
		set_prev_dir(*new_path, env);
		(free(*new_path), free(*prev_path));
		return (perror("cd"), env->last_status = 1, 1);
	}
}

void	set_prev_dir(char *dir, t_env *envp)
{
	if (envp->prev_dir)
		ft_mtclear(&envp->prev_dir);
	envp->prev_dir = create_prev_dir(dir);
	free(dir);
}
