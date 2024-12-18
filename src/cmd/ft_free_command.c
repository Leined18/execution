/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:22:11 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/18 12:44:51 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	free_command(t_command **cmd)
{
	if (cmd)
	{
		if ((*cmd)->args)
			free_2d((*cmd)->args);
		if ((*cmd)->cmd_path)
			free_null((void *)&(*cmd)->cmd_path);
		free(*cmd);
		*cmd = NULL;
	}
}
