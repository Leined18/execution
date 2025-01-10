/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:32:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/10 19:47:39 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_env_free(t_env *environ)
{
	if (environ->mt_env)
		ft_mtclear(&environ->mt_env);
	if (environ->mt_var)
		ft_mtclear(&environ->mt_var);
	if (environ->path)
		free_array2d(environ->path);
	if (environ->input)
		free(environ->input);
	if (environ->prompt)
		free(environ->prompt);
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
