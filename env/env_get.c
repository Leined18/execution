/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:38:20 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/18 17:31:57 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

//return a pointer to the value of the nave env.
char	*ft_getenv_value(const char *name, t_mt *envp)
{
	t_mt	*aux;

	aux = ft_mtfind_cmp(envp, (void *)name, ft_strncmp, ft_strlen(name));
	if (aux)
		return (aux->data + ft_strlen(name) + 1);
	return (NULL);
}

//return a pointer to the whole nave env.
char	*ft_getenv(const char *name, t_mt *envp)
{
	t_mt	*aux;

	aux = ft_mtfind_cmp(envp, (void *)name, ft_strncmp, ft_strlen(name));
	if (aux)
		return (aux->data);
	return (NULL);
}