/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/09 15:44:04 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
int	check_opt(char *opt)
{
	char	*clean_opt;

	clean_opt = ft_strtrim(opt, "'\"");
	if (ft_pmatch_str(clean_opt, "-n", 2) == 0)
		return (free(clean_opt), 1);
	return (free(clean_opt), 0);
}

int	echo_builtin(char **args, t_env *envp)
{
	int	i;
	int	opt;
	int	num_args;

	(void)envp;
	num_args = array2d_len(args);
	if (num_args > 1)
	{
		i = 1;
		opt = check_opt(args[i]);
		i += opt;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (i++ < num_args - 1)
				ft_printf(" ");
		}
		ft_printf("\n");
		if (!opt)
			ft_printf("\n");
	}
	return (0);
}
