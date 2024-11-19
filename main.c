/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/19 12:01:56 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// static void	del_content(void *content)
// {
// 	free(content);
// }

// int	free_nodes_lst(t_list **list)
// {
// 	t_list	*current;
// 	t_list	*next;

// 	if (list && *list)
// 	{
// 		current = *list;
// 		while (current)
// 		{
// 			next = current->next;
// 			ft_lstdelone(current, del_content);
// 			current = next;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// int	free_array2d(char **array)
// {
// 	int	i;

// 	if (array && *array)
// 	{
// 		i = 0;
// 		while (array[i])
// 		{
// 			free(array[i]);
// 			i++;
// 		}
// 		free(array);
// 		return (1);
// 	}
// 	return (0);
// }

// void	free_environment(t_env *environ)
// {
// 	free_nodes_lst(&environ->lst_env);
// 	free_array2d(environ->path);
// 	free(environ);
// }

// int	shell_loop(t_env *environ)
// {
// 	char	*input;

// 	while (1)
// 	{
// 		// Muestra el prompt y espera la entrada del usuario
// 		input = readline("MINISHELL>");
// 		// Si no puede leer, liberamos historial y salimos con 0(error)
// 		if (!input)
// 			return (rl_clear_history(), 0);
// 		// Si la entrada es "exit" salimos con 1 (correcto)
// 		if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
// 			return (free_null((void **)&input), rl_clear_history(), 1);
// 		// Si el usuario escribió algo, se agrega al historial y se procesa.
// 		if (*input)
// 		{
// 			add_history(input);
// 			cd_builtin(input, environ);
// 			//$DIVIDIR ENTRADA EN COMANDOS (PARSEAR Y DEMAS)
// 			//$se encargará de hacer el bucle en todos los comandos (desde solo 1 a n)
// 		}
// 		// liberamos input para leer uno nuevo y que no se quede sin liberar.
// 		free_null((void **)&input);
// 	}
// }

int	shell_loop(t_env *environ)
{
	char	*input;

	while (1)
	{
		// Muestra el prompt y espera la entrada del usuario
		input = readline("MINISHELL>");
		// Si no puede leer, liberamos historial y salimos con 0(error)
		// Si la entrada es "exit" salimos con 1 (correcto)
		if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
			return (free_null((void **)&input), rl_clear_history(), 1);
		// Si el usuario escribió algo, se agrega al historial y se procesa.
		if (*input)
			add_history(input);
		if (ft_strlen(input) == 3 && ft_strncmp(input, "env", 3) == 0)
			env_builtin(&environ->mt_env);
		else
			cd_builtin(input, environ);
		// liberamos input para leer uno nuevo y que no se quede sin liberar.
		free_null((void **)&input);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_env	*environ;

	(void)av;
	environ = NULL;
	if (ac != 1)
	{
		ft_printf("Usage: ./exe\n");
		return (0);
	}
	if (!copy_envp(&environ, ev))
		return (0);
	shell_loop(environ);
	// ft_printf("---------------ENV-------------------------------------------------------------------------\n");
	// env_builtin(&environ->mt_env);
	// ft_printf("---------------PATH---------------------------------------------------------------------------\n");
	// print_array(environ->path);
	// ft_printf("---------------PRUEBA DE CD--------------------------------------------------------------------\n");
	// cd_builtin(NULL, environ);
	// ft_printf("---------------ENV MODIFICADA---------------------------------------------------------------\n");
	// env_builtin(&environ->mt_env);
	// ft_mtprint(environ->mt_env, 1, "\n");
	// ft_printf("num_env = %d\n", environ->num_env);
	return (ft_successful(SUCCESS, 1), 0);
}
