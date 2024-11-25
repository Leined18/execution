#ifndef BUILTINS_H
# define BUILTINS_H

// Include any necessary headers here

# include "env.h"
# include "libft.h"

//ft_cd.c
int		cd_builtin(char *path, t_env *envp);

//ft_env.c
void	env_builtin(t_mt **first);
void	print_array(char **array);

//cd_utils.c
int		is_relative(char *path);

#endif // BUILTINS_H