/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:34 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/14 17:15:44 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// char	*ft_expand_old(char *str, t_env *envp)
// {
// 	char	*result;

// 	if (!str)
// 		return (NULL);
// 	if (str[0] != '$')
// 		return (ft_strdup(str));
// 	result = ft_getenv_value(str + 1, envp->mt_env);
// 	if (!result)
// 		result = ft_getenv_value(str + 1, envp->mt_var);
// 	return (result);
// }

char	*ft_expand(char *str, t_env *envp)
{
	char	*result;
	char	*expanded;
	char	*var_name;
	char	*var_value;
	char	*character;
	int		i;
	int		start;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			if (i > start)
			{
				var_name = ft_substr(str, start, i - start);
				var_value = ft_getenv_ptr_value(var_name, envp->mt_env);
				if (!var_value)
					var_value = ft_getenv_ptr_value(var_name, envp->mt_var);
				free(var_name);
				if (var_value)
					expanded = ft_strjoin(result, var_value);
				else
					expanded = ft_strjoin(result, "");
				free(result);
				result = expanded;
			}
		}
		else
		{
			character = ft_substr(str, i, 1);
			expanded = ft_strjoin(result, character);
			free(result);
			free(character);
			result = expanded;
			i++;
		}
	}
	return (result);
}
