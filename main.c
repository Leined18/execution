/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/21 17:32:18 by mvidal-h         ###   ########.fr       */
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

//Return the length of the value of env var named "name".
// If flag ==1 and var is "HOME" return 1. (~ in prompt).
//else return the normal length.
size_t	get_len_env(char *name, t_mt *mt_env, int flag)
{
	char	*value;
	char	*home;
	home = ft_getenv_value("HOME", mt_env, 0);
	value = ft_getenv_value(name, mt_env, 0);
	if (ft_find_env(value, home, ft_strlen(home)) == 0 && flag)
		return (1);
	else
		return (ft_strlen(value));
}

char	*generate_prompt(t_mt	*mt_env)
{
	char	*str_prompt;
	size_t	len;
	char *	prueba;
	
	len = 4;
	ft_printf("len = %d\n", len);
	len += ft_strlen(PURPLE);
	ft_printf("len = %d\n", len);
	len += ft_strlen("MINISHELL");
	ft_printf("len = %d\n", len);
	len += ft_strlen(GREEN);
	ft_printf("len = %d\n", len);
	len += get_len_env("PWD", mt_env, 1);
	ft_printf("len = %d\n", len);
	len += ft_strlen(RESET);
	ft_printf("len = %d\n", len);
	str_prompt = ft_calloc(len, sizeof(char));
	if (!str_prompt)
		return (NULL);
	ft_strlcat(str_prompt, PURPLE, len);
	ft_strlcat(str_prompt, "MINISHELL", len);
	ft_strlcat(str_prompt, ":", len);
	ft_strlcat(str_prompt, GREEN, len);
	prueba = ft_getenv_value("PWD", mt_env, 1); //SEGUIR AQUI
	ft_printf("prueba[0] = %s\n");
	ft_strlcat(str_prompt, prueba, len);
	//ft_strlcat(str_prompt, ft_getenv_value("PWD", mt_env, 1), len);
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
		input = readline(prompt);
		if (input == NULL)
			return (free(prompt), rl_clear_history() ,0);
		if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
			return (free(prompt), free_null((void **)&input), rl_clear_history(), 1);
		if (*input)
			add_history(input);
		if (ft_strlen(input) == 3 && ft_strncmp(input, "env", 3) == 0)
			env_builtin(&environ->mt_env);
		else if (ft_strlen(input) == 4 && ft_strncmp(input, "path", 4) == 0)
			print_lst_data(environ->path);
		else
			cd_builtin(input, environ);
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
