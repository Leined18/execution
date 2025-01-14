/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:34 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/14 09:23:45 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_expand(char *str, t_env *envp)
{
	char	*result;

	if (!str)
		return (NULL);
	if (str[0] != '$')
		return (ft_strdup(str));
	result = ft_getenv_value(str + 1, envp->mt_env);
	if (!result)
		result = ft_getenv_value(str + 1, envp->mt_var);
	return (result);
}