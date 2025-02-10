/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:32:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/10 11:31:59 by danpalac         ###   ########.fr       */
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
		free_null((void **)&environ->input);
	if (environ->prompt)
		free_null((void **)&environ->prompt);
	close_stdin_stdout(environ);
	free_null((void **)&environ);
}

void	ft_env_free_func(void **environ)
{
	t_env	*env;

	env = (t_env *)*environ;
	if (env->mt_env)
		ft_mtclear(&env->mt_env);
	if (env->mt_var)
		ft_mtclear(&env->mt_var);
	if (env->path)
		free_array2d(env->path);
	if (env->input)
		free_null((void **)&env->input);
	if (env->prompt)
		free_null((void **)&env->prompt);
	close_stdin_stdout(env);
	free_null(environ);
}
