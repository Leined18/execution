/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:43 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/10 12:35:29 by danpalac         ###   ########.fr       */
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

char	**mtbranch_array2d(t_mt *list, t_env *envp)
{
	char	**array;
	size_t	list_size;
	size_t	i;
	char	*aux;

	if (!list)
		return (NULL);
	i = 0;
	list_size = ft_mtcount_node(list->aux);
	array = ft_calloc(1 + list_size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	array[i++] = ft_expand(list->data, list->values.state, envp);
	list = list->aux;
	while (list)
	{
		aux = ft_expand(list->data, list->values.state, envp);
		if (*aux)
			array[i++] = aux;
		else
			free(aux);
		list = list->vect[RIGHT];
	}
	return (array);
}

t_command	*create_command(t_mt *parsed_cmd, t_env *envp)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		ft_error("Error al crear el comando\n", 1);
	new_command->command = ft_expand(parsed_cmd->data, parsed_cmd->values.state,
			envp);
	new_command->args = mtbranch_array2d(parsed_cmd, envp);
	new_command->cmd_path = get_cmd_path(envp->path, new_command->command);
	if (!*new_command->command)
		return (free_command(new_command), NULL);
	return (new_command);
}
