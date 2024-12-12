/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:51:27 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/12 13:37:48 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	*build_new_env(const char *name, const char *value, int total_len)
{
	char	*str;

	str = ft_calloc(total_len, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcat(str, name, total_len);
	ft_strlcat(str, "=", total_len);
	ft_strlcat(str, value, total_len);
	return (str);
}

int	ft_setenv(const char *name, const char *value, t_env *envp)
{
	int		len_name;
	int		total_len;
	char	*env_str;
	char	*new_env;

	len_name = ft_strlen(name);
	total_len = len_name + 1 + ft_strlen(value) + 1;
	env_str = ft_getenv(name, envp->mt_env);
	new_env = build_new_env(name, value, total_len);
	if (env_str)
		ft_mtreplace(&envp->mt_env, ft_mtsearch_list(envp->mt_env, name),ft_mtnew(name, new_env, STRING));
	else
	{
		env_str = ft_getenv(name, envp->mt_var);
		if (env_str)
			ft_mtreplace(&envp->mt_var, ft_mtsearch_list(envp->mt_var, name),ft_mtnew(name, new_env, STRING));
		else
		{
			ft_mtpush_data_back(&envp->mt_var, new_env, new_env, STRING);
			envp->num_var++;
		}
	}
	return (free(env_str), 0);
}
