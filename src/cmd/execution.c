/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:27:24 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/03 18:33:07 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	endizide_nodes(t_mt *node)
{
	if (!node || node->values.state == END)
		return (0);
	node->values.state = END;
	endizide_nodes(node->vect[LEFT]);
	endizide_nodes(node->vect[RIGHT]);
	return (0);
}

int	manage_redirection(t_mt *node)
{
	if (ft_pmatch_str(node->key, "<", 1))
		redirect_input(node, 0);
	else if (ft_pmatch_str(node->key, ">", 1))
		redirect_output(node, 1);
	else if (ft_pmatch_str(node->key, ">>", 2))
		redirect_output(node, 2);
	// else if (ft_pmatch_str(node->key, "&>", 2))
	// else if (ft_pmatch_str(node->key, "2>", 2))
	return (0);
}

void	restore_stdin_stdout(t_env *env)
{
	env->original_stdin = dup(STDIN_FILENO);
	env->original_stdout = dup(STDOUT_FILENO);
}

int	execute_tree(t_mt *node, t_env *env, int is_child)
{
	if (!node)
		return (1);
	if (node->values.state != END)
	{
		if (!is_ope_or_red(node))
		{
			if (ft_mtcheck_state(node, ASSIGNMENT))
				ft_assignation(node, env);
			else
				process_command(node, env, is_child);
		}
		else
		{
			if (ft_mtcheck_state(node, REDIRECTION))
				manage_redirection(node);
			else
			{
				execute_pipe(node, env);
				if (!is_child) //evita que una segunda pipe anidada haga END todos los nodos ya que al ser hijo no quedaria guardado. Sólo lo hace si es el padre original.
					endizide_nodes(node);
			}
		}
	}
	execute_tree(node->vect[LEFT], env, is_child);
	execute_tree(node->vect[RIGHT], env, is_child);
	restore_stdin_stdout(env);
	return (0);
}
