#ifndef BUILTIN_H
# define BUILTIN_H

// Include any necessary headers here

# include "libft.h"
# include "types.h"

//builtin.h
void init_builtins(t_builtin *builtins);
int execute_builtin(char **args, t_env *envp);

//ft_cd.c
//int		cd_builtin(char *path, t_env *envp);
int		cd_builtin(char **args, t_env *envp);

//ft_env.c
//int		env_builtin(t_mt **first);
int		env_builtin(char **args, t_env *envp);
void	print_array(char **array);

//ft_pwd.c
//int	    pwd_builtin(t_mt *mt_env);
int	    pwd_builtin(char **args, t_env *envp);

#endif // BUILTIN_H