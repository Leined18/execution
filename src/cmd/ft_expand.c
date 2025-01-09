/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:34 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/09 12:00:30 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_expand(char *str, t_env *envp)
{
	char	*result;

	if (!str || str[0] != '$')
		return (NULL);
	result = ft_getenv_ptr_value(str + 1, envp->mt_env);
	if (!result)
		result = ft_getenv_ptr_value(str + 1, envp->mt_var);
	return (result);
}