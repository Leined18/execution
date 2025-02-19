/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:27:24 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/19 17:57:53 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	manage_redirection(t_mt *node, t_env *env)
{
	int	result;

	if (ft_pmatch_str(node->key, "<", 1) == 0)
		result = redirect_input(node, 0, env);
	else if (ft_pmatch_str(node->key, ">", 1) == 0)
		result = redirect_output(node, 1, env);
	else if (ft_pmatch_str(node->key, ">>", 2) == 0)
		result = redirect_output(node, 2, env);
	else if (ft_pmatch_str(node->key, "<<", 2) == 0)
		result = redirect_heredoc(node, env);
	node->values.state = END;
	return (result);
}

// int	manage_logic_operator(t_mt *node, t_env *env, int is_child)
// {
// 	int	result;

// 	result = ft_execute_tree(node->vect[LEFT], env, is_child);
// 	if (ft_pmatch_str(node->key, "&&", 2) == 0)
// 	{
// 		if (result == 0)
// 			result = ft_execute_tree(node->vect[RIGHT], env, is_child);
// 		else
// 			if (!is_child)
// 				endizide_nodes(node);
// 	}
// 	else if (ft_pmatch_str(node->key, "||", 2) == 0)
// 	{
// 		if (result != 0)
// 			result = ft_execute_tree(node->vect[RIGHT], env, is_child);
// 		else
// 			if (!is_child)
// 				endizide_nodes(node);
// 	}
// 	node->values.state = END;
// 	return (result);
// }

int	ft_execute_tree(t_mt *node, t_env *env, int is_child)
{
	int	result;

	if (!node)
		return (0);
	result = 0;
	if (node->values.state != END)
	{
		if (!is_ope_or_red(node))
		{
			if (ft_mtcheck_state(node, COMMAND) && ft_strchr(node->key, '='))
				result = ft_assignation(node, env); //BIEN: devuelve 0 si todo bien, -1 si parametros no existen y un numero mayor que 0 dependiendo de en que argumento no es asignacion.
			else if (ft_mtcheck_state(node, PARENTESIS))
			{
				result = ft_execute_tree(node->aux, env, 0);//REVISAR
				node->values.state = END;
			}
			else
				result = process_command(node, env, is_child);//BIEN
		}
		else
		{
			if (ft_mtcheck_state(node, REDIRECTION))
				result = manage_redirection(node, env); //BIEN
			else if (ft_pmatch_str(node->key, "|", 1) == 0)
			{
				result = execute_pipe(node, env); //BIEN
				if (!is_child)
					// evita que una segunda pipe anidada haga END todos los nodos ya que al ser hijo no quedaria guardado. Sólo lo hace si es el padre original.
					endizide_nodes(node);
			}
			else
				ft_printf("manage_logic_operator\n"); //CONTINUAR MANAÑA AQUI
				// result = manage_logic_operator(node, env, is_child); //REVISAR
		}
	}
	if (result == 0)
	{
		result = ft_execute_tree(node->vect[LEFT], env, is_child);
		result = ft_execute_tree(node->vect[RIGHT], env, is_child);
	}
	return (result);
}
