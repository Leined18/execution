/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:07 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/03 13:06:59 by mvidal-h         ###   ########.fr       */
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

// int	is_in_single_quotes(char *str, int pos)
// {
// 	int	count;
// 	int	j;

// 	count = 0;
// 	j = 0;
// 	while (j < pos)
// 	{
// 		if (str[j] == '\'')
// 			count++;
// 		j++;
// 	}
// 	if (count % 2 == 0)
// 		return (0);
// 	j = pos + 1;
// 	while (str[j])
// 	{
// 		if (str[j] == '\'')
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

char	*expand_last_status(char *result, int *i, t_env *envp)
{
	char	*aux;
	char	*expanded;

	aux = ft_itoa(envp->last_status);
	expanded = ft_strjoin(result, aux);
	(*i)++;
	free(aux);
	return (expanded);
}
