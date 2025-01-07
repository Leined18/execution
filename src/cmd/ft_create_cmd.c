/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:43 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/03 11:34:01 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	print_command(t_command *cmd)
{
	ft_printf("----------cmd----------\n");
	ft_printf("cmd: %s\n", cmd->command);
	ft_printf("cmd: %s\n", cmd->cmd_path);
	print_array2d(cmd->args);
	ft_printf("-----------------------\n");
}

char	**mtbranch_array2d(t_mt *list)
{
	char	**array;
	size_t	list_size;
	size_t	i;

	if (!list)
		return (NULL);
	i = 0;
	list_size = ft_mtcount_node(list->aux);
	array = ft_calloc(1 + list_size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	array[i++] = ft_strdup(list->data);
	list = list->aux;
	while (list)
	{
		array[i++] = ft_strdup(list->data);
		list = list->vect[RIGHT];
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
	new_command->args = mtbranch_array2d(parsed_cmd);
	new_command->cmd_path = get_cmd_path(path, new_command->command);
	return (new_command);
}
