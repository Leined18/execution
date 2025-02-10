/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:07:44 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/10 11:48:50 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// Checks if command exists. First checks if command exists in every
// path of splith_path. If not, it checks if command exists as
// global path passed as parameter. It builds the path adding "/"
// and "cmd" to every path of split_path and check if it
// exists. If exists it returns the path.
char	*get_cmd_path(char **split_path, const char *cmd)
{
	int		i;
	char	*path;
	size_t	len;

	i = 0;
	if (!cmd)
		return (NULL);
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
			(ft_strlcat(path, "/", len), ft_strlcat(path, cmd, len));
			if (access(path, F_OK) == 0)
				return (path);
			free(path);
		}
	}
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
