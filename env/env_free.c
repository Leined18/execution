/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:32:22 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/03 13:34:41 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_env_free(void **environ)
{
	t_env	*env;

	env = (t_env *)*environ;
	ft_mtclear(&(env)->mt_env);
	ft_mtclear(&(env)->path);
	free_null(environ);
}
