/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/26 18:14:56 by mvidal-h         ###   ########.fr       */
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

static int	is_exit(t_command *cmd)
{
	if (ft_pmatch_str(cmd->command, "exit", 4) == 0)
	{
		if (cmd->args)
		{
			if (!ft_isstrnum(cmd->args[0]))
				return (1);
			else if (cmd->args[1])
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
	char		*input;
	char		*prompt;
	t_mt		*parsed_cmd;
	t_command	*cmd;

	while (1)
	{
		prompt = generate_prompt(environ->mt_env);
		input = readline(prompt);
		if (input == NULL)
			return (free(prompt), rl_clear_history(), 1);
		if (*input)
		{
			add_history(input);
			parsed_cmd = parse_input(input);
			cmd = create_command(parsed_cmd, environ->path);
			ft_mtclear(&parsed_cmd);
			//print_command(cmd);
			if (ft_pmatch_str(cmd->command, "path", 4) == 0)
			{
				print_array2d(environ->path);
				(free_command(cmd), free(prompt), free_null((void **)&input));
				continue;
			}
			else if (ft_strchr(cmd->command, '='))
			{
				ft_assignation(cmd, environ);
				(free_command(cmd), free(prompt), free_null((void **)&input));
				continue;
			}
			else if (ft_pmatch_str(cmd->command, "vars", 4) == 0)
			{
				print_lst_data(environ->mt_var);
				ft_printf("%d\n", environ->num_var);
				(free_command(cmd), free(prompt), free_null((void **)&input));
				continue;
			}
			if (is_exit(cmd))
				(free(prompt), free_null((void **)&input), rl_clear_history());
			execution(cmd, environ);
			free_command(cmd);
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
