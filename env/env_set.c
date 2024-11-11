/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:51:27 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/11 14:21:04 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_setenv(const char *name, const char *value, int overwrite, t_env	***envp)
{
	char	*var;
	int		len_name;
	int		len_value;
	int		total_len;
	int		i;

	var = NULL;
	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	total_len = len_name + 1 + len_value + 1;
	i = 0;
	while(!var && *envp[i])
		var = ft_strnstr(*envp[i], name, len_name);
	if(var)
		free(*envp[i]);
	*envp[i] = ft_calloc(len * (sizeof(char *)));
	if (*envp[i] == NULL)
		exit(1);
	ft_strlcat(*envp[i], name, total_len);
	ft_strlcat(*envp[i], "=", total_len);
	ft_strlcat(*envp[i], value, total_len);
}