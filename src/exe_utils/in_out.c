/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:52:59 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/06 16:15:23 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	close_stdin_stdout(t_env *env)
{
	close(env->redirect.original_stdin);
	close(env->redirect.original_stdout);
}

void	restore_stdin_stdout(t_env *env)
{
	if (env->redirect.is_red_in)
	{
		dup2(env->redirect.original_stdin, STDIN_FILENO);
		env->redirect.is_red_in = 0;
	}
	if (env->redirect.is_red_out)
	{
		dup2(env->redirect.original_stdout, STDOUT_FILENO);
		env->redirect.is_red_out = 0;
	}
}
