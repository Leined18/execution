/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:34 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/10 12:09:34 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_in_expansible(char *str, int *i, char *result, t_env *envp)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*expanded;
	char	*aux;

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
	}
	if (str[start] == '?' && (str[start + 1] == ' ' || str[start + 1] == '\0'))
	{
		aux = ft_itoa(envp->last_status);
		expanded = ft_strjoin(result, aux);
		((*i)++, free(aux));
	}
	return (free(result), expanded);
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

char	*ft_expand(char *str, int state, t_env *envp)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	if (ft_pmatch_str(str, "$?", 2) == 0)
		return (ft_itoa(envp->last_status));
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && state != SINGLE_QUOTE)
			result = ft_in_expansible(str, &i, result, envp);
		else
		{
			result = ft_not_in_expansible(str, i, result);
			i++;
		}
	}
	return (result);
}

// REVISAR ESTO DA ERROR: echo 'hola que tal '$HOSTNAME' adios'
