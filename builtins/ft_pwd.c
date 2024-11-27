/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:09:43 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/27 18:50:51 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	pwd_builtin(char **args, t_env *envp)
{
	(void)args;
	ft_printf("%s\n", ft_getenv_value("PWD", envp->mt_env));
	return (0);
}