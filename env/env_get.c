/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:38:20 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/26 19:46:00 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

//compare two strings and return 0 if both are exactly the same.
int ft_pmatch_str(const char *s1, const char *s2, size_t n)
{
	// Comparar los primeros n caracteres
	if (ft_strncmp(s1, s2, n) != 0)
		return 1;
	// Verificar que el siguiente carácter sea el delimitador o el final de la cadena
	if (s1[n] != '\0')
		return 1;
	return 0; // Coincidencia exacta
}

int ft_pmatch_env(const char *s1, const char *s2, size_t n)
{
	// Comparar los primeros n caracteres
	if (ft_strncmp(s1, s2, n) != 0)
		return 1;
	// Verificar que el siguiente carácter sea el delimitador o el final de la cadena
	if (s1[n] != '=')
		return 1;
	return 0; // Coincidencia exacta
}

//return a copy of the value of the name env.
char	*ft_getenv_value(const char *name, t_mt *envp)
{
	t_mt	*aux;

	aux = ft_mtfind_cmp(envp, (void *)name, ft_pmatch_env, ft_strlen(name));
	if (aux)
		return (aux->data + ft_strlen(name) + 1);
	return (NULL);
}

//return a copy of the whole env.
char	*ft_getenv(const char *name, t_mt *envp)
{
	t_mt	*aux;

	aux = ft_mtfind_cmp(envp, (void *)name, ft_pmatch_env, ft_strlen(name));
	if (aux)
		return (aux->data);
	return (NULL);
}