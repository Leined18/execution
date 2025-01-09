/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:37:03 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/01/09 11:51:05 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "exe.h"
# include "libft.h"

//env_init.c
char	**split_path_env(char *env[]);
t_env	*copy_envp(char **envp);
//env_set.c
int	ft_setenv(const char *name, const char *value, t_env *envp, int is_env);
//env_get.c
char	*ft_getenv(const char *name, t_mt *envp);
char	*ft_getenv_value(const char *name, t_mt *envp);
char	*ft_getenv_ptr_value(const char *name, t_mt *envp);
size_t	get_len_env(char *name, t_mt *mt_env, int flag);
int		ft_pmatch_env(const char *s1, const char *s2, size_t n);
int		ft_pmatch_str(const char *s1, const char *s2, size_t n);
//env_free.c
void	ft_env_free(t_env *environ);
void	ft_env_free_func(void **environ);
// LUEGO CAMBIAR
char	*ft_strrtrim(char const *s1, char const *set);
char	*ft_strltrim(char const *s1, char const *set);

#endif // ENV_H