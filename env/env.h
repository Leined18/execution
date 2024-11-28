/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:37:03 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/11/28 18:10:26 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "exe.h"

void	print_lst_data(t_mt *array);
int		copy_envp(t_env **environ, char **envp);
int		ft_setenv(const char *name, const char *value, t_mt *envp);
//env_get.c
char	*ft_getenv(const char *name, t_mt *envp);
char	*ft_getenv_value(const char *name, t_mt *envp);
size_t	get_len_env(char *name, t_mt *mt_env, int flag);
int		ft_pmatch_env(const char *s1, const char *s2, size_t n);
int		ft_pmatch_str(const char *s1, const char *s2, size_t n);
//LUEGO CAMBIAR
char	*ft_strrtrim(char const *s1, char const *set);
char	*ft_strltrim(char const *s1, char const *set);

#endif // ENV_H