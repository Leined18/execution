/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:51:27 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/14 18:21:10 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_setenv(const char *name, const char *value, t_mt **envp)
{
	int		len_name;
	int		len_value;
	int		total_len;
	t_mt	*aux;
	char	*env_str;
	char	*new_env;
	t_mt	*node_env;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	total_len = len_name + 1 + len_value + 1;
	env_str = NULL;
	if (envp != NULL)
	{
		aux = *envp;
		while (!env_str && aux)
		{
			env_str = ft_strnstr((char *)aux->data, name, len_name);
			if(!env_str)
				aux = aux->next;
		}
		new_env = chaosmatrix(total_len, sizeof(char *), 0);
		if (new_env == NULL)
			return (0);
		ft_strlcat(new_env, name, total_len);
		ft_strlcat(new_env, "=", total_len);
		ft_strlcat(new_env, value, total_len);
		if(env_str)
		{
			
			//free(aux->data);
			aux->data = (void *)new_env;
		}
		else
		{
			node_env = ft_mtnew_chaos((void *)new_env);
			if (!node_env)
				return (0);
			ft_mtadd_back(envp, node_env);
		}
		return (1);
	}
	return (0);
}
