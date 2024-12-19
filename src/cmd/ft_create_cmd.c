/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:43 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/19 12:29:52 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// t_command	*create_command(char *cmd, char *arg)
// {
// 	t_command	*new_command;

// 	new_command = malloc(sizeof(t_command));
// 	if (!new_command)
// 		ft_error("Error al crear el comando\n", 1);
// 	new_command->command = cmd;
// 	new_command->args = malloc(3 * sizeof(char *));
// 	if (!new_command->args)
// 		ft_error("Error al crear los argumentos\n", 1);
// 	new_command->args[0] = cmd;
// 	new_command->args[1] = arg;
// 	new_command->args[2] = NULL;
// 	return (new_command);
// }

void	print_command(t_command *cmd)
{
	ft_printf("----------cmd----------\n");
	ft_printf("cmd: %s\n", cmd->command);
	ft_printf("cmd: %s\n", cmd->cmd_path);
	print_array2d(cmd->args);
	ft_printf("-----------------------\n");
}

//Checks if command exists. First checks if command exists in every
// path of splith_path. If not, it checks if command exists as 
//global path passed as parameter. It builds the path adding "/" 
//and "cmd" to every path of split_path and check if it
// exists. If exists it returns the path.
char	*find_cmd_in_path(char **split_path, const char *cmd)
{
	int		i;
	char	*path;
	size_t	len;

	i = 0;
	path = NULL;
	if (split_path)
	{
		while (split_path[i])
		{
			len = (ft_strlen(split_path[i]) + ft_strlen(cmd) + 2);
			path = (char *)ft_calloc(len, sizeof(char));
			if (path == NULL)
				exit(1);
			ft_strlcat(path, split_path[i++], len);
			ft_strlcat(path, "/", len);
			ft_strlcat(path, cmd, len);
			if (access(path, F_OK) == 0)
				return (path);
			free(path);
		}
	}
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	**mtconvert_array2d(t_mt *list)
{
	char	**array;
	size_t	list_size;
	size_t	i;

	if (!list)
		return (NULL);
	i = 0;
	list_size = ft_mtcount_node(list);
	array = ft_calloc(list_size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	while (list)
	{
		array[i++] = ft_strdup(list->data);
		list = list->right;
	}
	return (array);
}

t_command	*create_command(t_mt *parsed_cmd, char **path)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		ft_error("Error al crear el comando\n", 1);
	new_command->command = ft_strdup(parsed_cmd->data);
	new_command->args = mtconvert_array2d(parsed_cmd->children);
	new_command->cmd_path = find_cmd_in_path(path, new_command->command);
	return (new_command);
}
