/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:34 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/14 18:53:07 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_in_expansible(char *str, int *i, char *result, t_env *envp)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*expanded;

	start = ++(*i);
	expanded = NULL;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i > start)
	{
		var_name = ft_substr(str, start, *i - start);
		var_value = ft_getenv_ptr_value(var_name, envp->mt_env);
		if (!var_value)
			var_value = ft_getenv_ptr_value(var_name, envp->mt_var);
		free(var_name);
		if (var_value)
			expanded = ft_strjoin(result, var_value);
		else
			expanded = ft_strjoin(result, "");
		free(result);
	}
	return (expanded);
}

char	*ft_not_in_expansible(char *str, int i, char *result)
{
		char	*character;
		char	*expanded;

		character = ft_substr(str, i, 1);
		expanded = ft_strjoin(result, character);
		free(result);
		free(character);
		return (expanded);
}

char	*ft_expand(char *str, t_env *envp)
{
	char	*result;
	int		i;
	
	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			result = ft_in_expansible(str, &i, result, envp);
		else
		{
			result = ft_not_in_expansible(str, i, result);
			i++;
		}
	}
	return (result);
}
