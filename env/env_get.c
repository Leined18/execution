/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:38:20 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/03 13:30:34 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// compare two strings and return 0 if both are exactly the same.
int	ft_pmatch_str(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	// Comparar los primeros n caracteres
	if (ft_strncmp(s1, s2, n) != 0)
		return (1);
	// Verificar que el siguiente carácter sea el delimitador o el final de la cadena
	if (s1[n] != '\0')
		return (1);
	return (0); // Coincidencia exacta
}

int	ft_pmatch_env(const char *s1, const char *s2, size_t n)
{
    if (!s1 || !s2)
        return (1);
	// Comparar los primeros n caracteres
	if (ft_strncmp(s1, s2, n) != 0)
		return (1);
	// Verificar que el siguiente carácter sea el delimitador o el final de la cadena
	if (s1[n] != '=')
		return (1);
	return (0); // Coincidencia exacta
}

size_t	get_len_env(char *name, t_mt *mt_env, int flag)
{
	char	*value;
	char	*home;
	size_t	len;

	home = ft_getenv_value("HOME", mt_env);
	value = ft_getenv_value(name, mt_env);
	if (ft_pmatch_str(value, home, ft_strlen(home)) == 0 && flag)
		len = 1;
	else
		len = ft_strlen(value);
	return (free(home), free(value), len);
}

// return a copy of the value of the name env.
char	*ft_getenv_value(const char *name, t_mt *envp)
{
	t_mt	*aux;

	aux = ft_mtsearch_list(envp, name);
	if (aux)
		return (ft_strdup(aux->data + ft_strlen(name) + 1));
	return (NULL);
}

// return a copy of the whole env.
char	*ft_getenv(const char *name, t_mt *envp)
{
	t_mt	*aux;

	aux = ft_mtsearch_list(envp, name);
	if (aux)
		return (ft_strdup(aux->data));
	return (NULL);
}
