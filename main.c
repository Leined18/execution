/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/11 17:58:08 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	del_content(void *content)
{
	free(content);
}

int	free_nodes_lst(t_list **list)
{
	t_list	*aux;

	if (list != NULL)
	{
		aux = *list;
		while (aux)
		{
			ft_lstdelone(aux,del_content);
			aux = aux->next;
		}
		return (1);
	}
	return (0);
}

void	free_array2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// int	free_environment()
// {
	
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
	/* sigaction_setup(&sigaction_handler);
	if (!shell_loop(&mem))
		return (clean_up(&mem), ft_error(ERROR, 0), 0); */
	env_builtin(&environ->lst_env);
	print_array(environ->path);
	free_nodes_lst(&environ->lst_env);
	free_array2d(environ->path);
	free(environ);
	return (ft_successful(SUCCESS, 1), 0);
}
