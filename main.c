/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/14 10:07:17 by mvidal-h         ###   ########.fr       */
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

// static int	is_exit(t_command *cmd)
// {
// 	if (ft_pmatch_str(cmd->command, "exit", 4) == 0)
// 	{
// 		if (cmd->args)
// 		{
// 			if (!ft_isstrnum(cmd->args[0]))
// 				return (1);
// 			else if (cmd->args[1])
// 				return (0);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }


int	shell_loop(t_env *env)
{
	t_mt		*parsed_cmd;
	t_command	*cmd;

	while (1)
	{
		env->prompt = generate_prompt(env->mt_env);
		env->input = readline(env->prompt);
		if (env->input == NULL)
			return (free(env->prompt), rl_clear_history(), 1);
		if (*env->input)
		{
			add_history(env->input);
			parsed_cmd = ft_parse_input(env->input);
			cmd = create_command(parsed_cmd, env);
			//print_command(cmd);
			if (ft_pmatch_str(cmd->command, "path", 4) == 0)
			{
				print_array2d(env->path);
				ft_mtclear(&parsed_cmd);
				(free_command(cmd), free(env->prompt), free_null((void **)&env->input));
				continue;
			}
			else if (ft_strchr(cmd->command, '='))
			{
				ft_assignation(parsed_cmd, env);
				ft_mtclear(&parsed_cmd);
				(free_command(cmd), free(env->prompt), free_null((void **)&env->input));
				continue;
			}
			else if (ft_pmatch_str(cmd->command, "vars", 4) == 0)
			{
				print_lst_data(env->mt_var);
				ft_printf("%d\n", env->num_var);
				ft_mtclear(&parsed_cmd);
				(free_command(cmd), free(env->prompt), free_null((void **)&env->input));
				continue;
			}
			ft_mtclear(&parsed_cmd);
			execution(cmd, env);
			free_command(cmd);
		}
		(free(env->prompt), free_null((void **)&env->input));
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
