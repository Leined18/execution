/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:37:03 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/03 12:40:23 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "exe.h"
# include "libft.h"

void	print_lst_data(t_mt *array);
t_env	*copy_envp(char **envp);
int		ft_setenv(const char *name, const char *value, t_mt *envp);
// env_get.c
char	*ft_getenv(const char *name, t_mt *envp);
char	*ft_getenv_value(const char *name, t_mt *envp);
size_t	get_len_env(char *name, t_mt *mt_env, int flag);
int		ft_pmatch_env(const char *s1, const char *s2, size_t n);
int		ft_pmatch_str(const char *s1, const char *s2, size_t n);
// LUEGO CAMBIAR
char	*ft_strrtrim(char const *s1, char const *set);
char	*ft_strltrim(char const *s1, char const *set);

#endif // ENV_H