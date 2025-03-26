/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/02/26 11:09:32 by mvidal-h         ###   ########.fr       */
=======
/*   Updated: 2025/03/26 11:32:03 by danpalac         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

<<<<<<< Updated upstream
int	shell_loop(t_env *env)
=======
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
	feature_loop(environ);
	ft_env_free(environ);
	return (ft_successful(SUCCESS, 1), 0);
}

/* int	feature_loop(t_env *env)
>>>>>>> Stashed changes
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
				(free_command(cmd), free(env->prompt),
					free_null((void **)&env->input));
				continue ;
			}
			else if (ft_strchr(cmd->command, '='))
			{
				ft_assignation(parsed_cmd, env);
				ft_mtclear(&parsed_cmd);
				(free_command(cmd), free(env->prompt),
					free_null((void **)&env->input));
				continue ;
			}
			else if (ft_pmatch_str(cmd->command, "vars", 4) == 0)
			{
				print_lst_data(env->mt_var);
				ft_printf("%d\n", env->num_var);
				ft_mtclear(&parsed_cmd);
				(free_command(cmd), free(env->prompt),
					free_null((void **)&env->input));
				continue ;
			}
			ft_mtclear(&parsed_cmd);
			execution(cmd, env);
			free_command(cmd);
		}
		(free(env->prompt), free_null((void **)&env->input));
	}
<<<<<<< Updated upstream
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
=======
} */
>>>>>>> Stashed changes
