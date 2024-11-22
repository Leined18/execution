/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:51:27 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/22 14:41:29 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	*build_new_env(const char *name, const char *value, int total_len)
{
		char	*str;
		
		str = chaosmatrix(total_len, sizeof(char), 0);
		if (str == NULL)
			return (NULL);
		ft_strlcat(str, name, total_len);
		ft_strlcat(str, "=", total_len);
		ft_strlcat(str, value, total_len);
		return (str);
}

int	ft_setenv(const char *name, const char *value, t_mt *envp)
{
	int		len_name;
	int		total_len;
	char	*env_str;
	char	*new_env;

	len_name = ft_strlen(name);
	total_len = len_name + 1 + ft_strlen(value) + 1;
	env_str = NULL;
	if (envp != NULL)
	{
		env_str = ft_getenv(name, envp);
		new_env = build_new_env(name, value, total_len);
		if(env_str)
			ft_mtreplace_data(envp, env_str, new_env, ft_strncmp, ft_strlen(env_str));
		else
			ft_mtpush_data_back(&envp, new_env);
		return (1);
	}
	return (0);
}
