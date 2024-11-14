/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/14 20:12:14 by mvidal-h         ###   ########.fr       */
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

int	main(int ac, char **av, char **ev)
{
	t_env *environ;

	(void)av;
	if (ac != 1)
	{
		ft_printf("Usage: ./exe\n");
		return (0);
	}
	if(!copy_envp(&environ, ev))
		return (0);
	ft_printf("---------------ENV---------------\n");
	env_builtin(&environ->mt_env);
	ft_printf("---------------PATH---------------\n");
	print_array(environ->path);
	// ft_printf("---------------PRUEBA DE CD---------------\n");
	// cd_builtin(NULL, environ);
	// ft_printf("---------------ENV MODIFICADA---------------\n");
	// env_builtin(&environ->mt_env);
	ft_printf("num_env = %d\n", environ->num_env);
	chaosmatrix(0, 0, -1);
	return (ft_successful(SUCCESS, 1), 0);
}
