/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:32:22 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/19 12:32:12 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_env_free(t_env *environ)
{
	ft_mtclear(&environ->mt_env);
	ft_mtclear(&environ->mt_var);
	free_array2d(environ->path);
	free_null((void **)&environ);
}

void 	ft_env_free_func(void **environ)
{
	t_env	*env;

	env = (t_env *)*environ;
	ft_mtclear(&env->mt_env);
	ft_mtclear(&env->mt_var);
	free_array2d(env->path);
	free_null(environ);
}
