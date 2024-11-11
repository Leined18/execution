/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:06 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/11 13:34:17 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_builtin(char *path, t_env ***envp)
		// En progreso. ¿Quizas pasarle un t_command y añadirle t_env en el t_command?
{
	char *prev_path;

	// Obtener el directorio de trabajo actual (sera el anterior)
	(void)envp;
	prev_path = getcwd(NULL, 0);
	if (prev_path == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%s es el directorio antiguo\n", prev_path);
	// Si solo se ha escrito cd (sin ruta)
	if (path == NULL)
		path = getenv("HOME");
	// Cambio de directorio
	if (chdir(path) != 0)
	{
		perror("cd");
		return (2);
	}
	ft_printf("Estoy en %s\n", path);
	return (free(prev_path), 0);
}
