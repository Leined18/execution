/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 16:46:54 by mvidal-h         ###   ########.fr       */
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
	return (ptr);
} */

static int	is_exit(char **splitted)
{
	if (ft_pmatch_str(splitted[0], "exit", 4) == 0)
	{
		if (splitted[1])
		{
			if (!ft_isstrnum(splitted[1]))
				return (1);
			else if (splitted[2])
				return (0);
		}
		return (1);
	}
	return (0);
}

int	pwd_is_home(t_mt *mt_env)
{
	char	*pwd;
	char	*home;

	pwd = ft_getenv_value("PWD", mt_env);
	home = ft_getenv_value("HOME", mt_env);
	if (ft_pmatch_str(pwd, home, ft_strlen(home)))
		return (free(home), free(pwd), 0);
	else
		return (free(home), free(pwd), 1);
}

char	*generate_prompt(t_mt *mt_env)
{
	char	*str_prompt;
	char	*pwd;
	size_t	len;

	len = ft_strlen(PURPLE) + ft_strlen("MINISHELL") + ft_strlen(GREEN);
	len += get_len_env("PWD", mt_env, 1);
	len += ft_strlen(RESET) + 4;
	str_prompt = ft_calloc(len, sizeof(char));
	if (!str_prompt)
		return (NULL);
	ft_strlcat(str_prompt, PURPLE, len);
	ft_strlcat(str_prompt, "MINISHELL", len);
	ft_strlcat(str_prompt, ":", len);
	ft_strlcat(str_prompt, GREEN, len);
	if (pwd_is_home(mt_env))
		ft_strlcat(str_prompt, "~", len);
	else
	{
		pwd = ft_getenv_value("PWD", mt_env);
		ft_strlcat(str_prompt, pwd, len);
		free(pwd);
	}
	ft_strlcat(str_prompt, "$ ", len);
	ft_strlcat(str_prompt, RESET, len);
	return (str_prompt);
}

int	shell_loop(t_env *environ)
{
	char	*input;
	char	*prompt;
	char	**splitted;

	while (1)
	{
		prompt = generate_prompt(environ->mt_env);
		input = readline(prompt);
		if (input == NULL)
			return (free(prompt), rl_clear_history(), 1);
		if (*input)
		{
			add_history(input);
			splitted = ft_split(input, ' ');
			if (ft_pmatch_str(splitted[0], "path", 4) == 0)
			{
				print_lst_data(environ->path);
				(free_array2d(splitted), free(prompt), free_null((void **)&input));
				continue;
			}
			else if (ft_pmatch_str(splitted[0], "create", 6) == 0)
			{
				ft_setenv(splitted[1], splitted[2], &environ->mt_var, &environ->num_var);
				(free_array2d(splitted), free(prompt), free_null((void **)&input));
				continue;
			}
			else if (ft_pmatch_str(splitted[0], "vars", 4) == 0)
			{
				print_lst_data(environ->mt_var);
				(free_array2d(splitted), free(prompt), free_null((void **)&input));
				continue;
			}
			else if (is_exit(splitted))
				(free(prompt), free_null((void **)&input), rl_clear_history());
			execute_builtin(splitted, environ);
			free_array2d(splitted);
		}
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
	environ = copy_envp(ev);
	if (!environ)
		return (ft_error(ERROR, 0), 1);
	shell_loop(environ);
	ft_env_free(environ);
	return (ft_successful(SUCCESS, 1), 0);
}
