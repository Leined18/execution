/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:32:22 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 16:52:39 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	free_array2d(char **array)
{
	int	i;

	if (array && *array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (1);
	}
	return (0);
}

void	ft_env_free(t_env *environ)
{
	ft_mtclear(&environ->mt_env);
	ft_mtclear(&environ->mt_var);
	ft_mtclear(&environ->path);
	free_null((void **)&environ);
}

void 	ft_env_free_func(void **environ)
{
	t_env	*env;

	env = (t_env *)*environ;
	ft_mtclear(&env->mt_env);
	ft_mtclear(&env->mt_var);
	ft_mtclear(&env->path);
	free_null(environ);
}
