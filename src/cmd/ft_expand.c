/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:34 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/27 17:46:18 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*join_value_var(char *var_name, char *result, t_env *envp)
{
	char	*var_value;

	var_value = ft_getenv_ptr_value(var_name, envp->mt_env);
	if (!var_value)
		var_value = ft_getenv_ptr_value(var_name, envp->mt_var);
	if (var_value)
		return (ft_strjoin(result, var_value));
	else
		return (ft_strjoin(result, ""));
}

int	is_in_single_quotes(char *str, int pos)
{
	int	in_quotes;
	int	j;

	in_quotes = 0;
	j = 0;
	while (j < pos)
	{
		if (str[j] == '\'')
			in_quotes = !in_quotes;
		j++;
	}
	return (in_quotes);
}

char	*ft_in_expansible(char *str, int *i, char *result, t_env *envp)
{
	int		start;
	char	*expanded;
	char	*aux;
	char	*var_name;

	if (is_in_single_quotes(str, *i))
	{
		expanded = ft_strjoin(result, "$");
		(*i)++;
		return (free(result), expanded);
	}
	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i > start)
	{
		var_name = ft_substr(str, start, *i - start);
		expanded = join_value_var(var_name, result, envp);
		free(var_name);
	}
	else if (str[start] == '?')
	{
		aux = ft_itoa(envp->last_status);
		expanded = ft_strjoin(result, aux);
		(*i)++;
		free(aux);
	}
	else
		expanded = ft_strjoin(result, "");
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
