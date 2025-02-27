/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:11:17 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/27 09:12:20 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	pwd_is_home(t_mt *mt_env)
{
	char	*pwd;
	char	*home;

	pwd = ft_getenv_value("PWD", mt_env);
	home = ft_getenv_value("HOME", mt_env);
	if (ft_pmatch_str(pwd, home, ft_strlen(home)))
		return (free(home), free(pwd), 0);
	else
		return (free(home), free(pwd), 1);
}

char	*generate_prompt(t_mt *mt_env)
{
	char	*str_prompt;
	char	*pwd;
	size_t	len;

	len = ft_strlen(PURPLE) + ft_strlen("MINISHELL") + ft_strlen(GREEN);
	len += get_len_env("PWD", mt_env, 1);
	len += ft_strlen(RESET) + 4;
	str_prompt = ft_calloc(len, sizeof(char));
	if (!str_prompt)
		return (NULL);
	ft_strlcat(str_prompt, PURPLE, len);
	ft_strlcat(str_prompt, "MINISHELL", len);
	ft_strlcat(str_prompt, ":", len);
	ft_strlcat(str_prompt, GREEN, len);
	if (pwd_is_home(mt_env))
		ft_strlcat(str_prompt, "~", len);
	else
	{
		pwd = ft_getenv_value("PWD", mt_env);
		ft_strlcat(str_prompt, pwd, len);
		free(pwd);
	}
	ft_strlcat(str_prompt, "$ ", len);
	ft_strlcat(str_prompt, RESET, len);
	return (str_prompt);
}
