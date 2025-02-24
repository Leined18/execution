/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:28:07 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/24 19:29:35 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int ft_fnmatch(const char *pattern, const char *str)
{
	const char *star = NULL;
	const char *backup = NULL;
	
	while (*str) {
		if (*pattern == '*')
		{// Guardamos la posición de '*' como resplado y avanzamos en pattern a la siguiente posición
			star = pattern++;
			backup = str; //guardamos la posicion de str para retroceder en caso de no coincidir
		} else if (*pattern == *str)
		{// Si coinciden avanzamos en ambas cadenas.
			pattern++;
			str++;
		} else if (star)
		{// Si hay un '*' anterior, retrocedemos pattern y avanzamos str
			pattern = star + 1;
			str = ++backup;
		} else // No coinciden y no había un '*' como respaldo.
			return (0);
	}
	while (*pattern == '*') // Si ya se llegó al final de str se ignoran los '*' restantes
		pattern++;
	return (*pattern == '\0'); // Si los dos están en final de cadena, es un match.
}

int count_wildcard(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	int				count;

	dir = opendir("."); // Abre el directorio actual
	if (!dir)
		return (perror("opendir"), 0);
	count = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.') // Ignorar archivos ocultos (los que empiezan con '.')
			continue;
		if (ft_fnmatch(pattern, entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}

void expand_wildcard(char *pattern, char **args, size_t *i)
{
	struct dirent *entry;
	DIR *dir;

	dir = opendir("."); // Abre el directorio actual
	if (!dir) {
		perror("opendir");
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.') // Ignorar archivos ocultos (los que empiezan con '.')
			continue;
		if (ft_fnmatch(pattern, entry->d_name))
			args[(*i)++] = strdup(entry->d_name);
	}
	closedir(dir);
}
