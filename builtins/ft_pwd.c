/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:09:43 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/09 15:39:16 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	pwd_builtin(char **args, t_env *envp)
{
	char	*pwd;

	(void)args;
	pwd = ft_getenv_value("PWD", envp->mt_env);
	ft_printf("%s\n", pwd);
	ft_printf("\n");
	return (free(pwd), 0);
}