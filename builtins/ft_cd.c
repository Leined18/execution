/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/20 13:58:32 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_builtin(char *path, t_env *envp) //todavia sin rutas relativas ni .. ni -
{
	char	*prev_path;

	// Obtener el directorio de trabajo actual (sera el anterior)
	prev_path = getcwd(NULL, 0);
	if (prev_path == NULL)
		return (perror("getcwd"), 0);
	// Si solo se ha escrito cd (sin ruta)
	if (!(*path))
		path = ft_getenv_value("HOME", envp->mt_env);
	// Cambio de directorio
	if (chdir(path) != 0)
		return (free(prev_path), perror("cd"), 0);
	ft_setenv("PWD", path, envp->mt_env);
	ft_setenv("OLDPWD", prev_path, envp->mt_env);
	return (free(prev_path), 0);
}
