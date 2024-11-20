/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/20 18:51:33 by mvidal-h         ###   ########.fr       */
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

/* void *cortexarchive(int count, size_t size, t_mt **list) FUTURO
{
	void *ptr;
	t_mt *new_node;

	ptr = malloc(count * size);

	new_node = ft_mtnew(ptr);
	ft_mtadd_back(list, new_node);
	return ptr;
} */

char	*generate_prompt(t_mt	*mt_env)
{
	char	*str_prompt;
	size_t	len;
	
	len = 5;
	len += ft_strlen(PURPLE);
	len += ft_strlen(ft_getenv_value("USER", mt_env));
	len += ft_strlen(ft_getenv_value("HOSTNAME", mt_env));
	len += ft_strlen(YELLOW);
	len += ft_strlen(ft_getenv_value("PWD", mt_env));
	len += ft_strlen(RESET);
	str_prompt = ft_calloc(len, sizeof(char));
	if (!str_prompt)
		return (NULL);
	ft_strlcat(str_prompt, PURPLE, len);
	ft_strlcat(str_prompt, ft_getenv_value("USER", mt_env), len);
	ft_strlcat(str_prompt, "@", len);
	ft_strlcat(str_prompt, ft_getenv_value("HOSTNAME", mt_env), len);
	ft_strlcat(str_prompt, ":", len);
	ft_strlcat(str_prompt, YELLOW, len);
	ft_strlcat(str_prompt, ft_getenv_value("PWD", mt_env), len);
	ft_strlcat(str_prompt, "$ ", len);
	ft_strlcat(str_prompt, RESET, len);
	return (str_prompt);
}

int	shell_loop(t_env *environ)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = generate_prompt(environ->mt_env);
		// Muestra el prompt y espera la entrada del usuario
		input = readline(prompt);
		// Si no puede leer, liberamos historial y salimos con 0(error)
		if (input == NULL)
			return (free(prompt), rl_clear_history() ,0);
		// Si la entrada es "exit" salimos con 1 (correcto)
		if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
			return (free(prompt), free_null((void **)&input), rl_clear_history(), 1);
		// Si el usuario escribió algo, se agrega al historial y se procesa.
		if (*input)
			add_history(input);
		if (ft_strlen(input) == 3 && ft_strncmp(input, "env", 3) == 0)
			env_builtin(&environ->mt_env);
		else if (ft_strlen(input) == 4 && ft_strncmp(input, "path", 4) == 0)
			print_lst_data(environ->path);
		else
			cd_builtin(input, environ);
		// liberamos input para leer uno nuevo y que no se quede sin liberar.
		(free(prompt), free_null((void **)&input));
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
	return (ft_successful(SUCCESS, 1), 0);
}
