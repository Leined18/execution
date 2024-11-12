/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:51:27 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/12 17:31:04 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_setenv(const char *name, const char *value, t_list **envp)
{
	int		len_name;
	int		len_value;
	int		total_len;
	t_list	*aux;
	char	*env_str;
	char	*new_env;
	t_list	*node_env;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	total_len = len_name + 1 + len_value + 1;
	env_str = NULL;
	if (envp != NULL)
	{
		aux = *envp;
		while (!env_str && aux)
		{
			env_str = ft_strnstr((char *)aux->content, name, len_name);
			if(!env_str)
				aux = aux->next;
		}
		new_env = ft_calloc(total_len, sizeof(char *));
		if (new_env == NULL)
			return (0);
		ft_strlcat(new_env, name, total_len);
		ft_strlcat(new_env, "=", total_len);
		ft_strlcat(new_env, value, total_len);
		if(env_str)
		{
			free(aux->content);
			aux->content = (void *)new_env;
		}
		else
		{
			node_env = ft_lstnew((void *)new_env);
			if (!node_env)
				return (free(new_env), 0);
			ft_lstadd_back(envp, node_env);
		}
		return (1);
	}
	return (0);
}
