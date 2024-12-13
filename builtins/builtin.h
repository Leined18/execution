#ifndef BUILTIN_H
# define BUILTIN_H

// Include any necessary headers here

# include "libft.h"
# include "types.h"

//builtin.h
void init_builtins(t_builtin *builtins);
int execute_builtin(char **args, t_env *envp);

//ft_cd.c
int		cd_builtin(char **args, t_env *envp);

//ft_env.c
int		env_builtin(char **args, t_env *envp);

//ft_pwd.c
int		pwd_builtin(char **args, t_env *envp);

//ft_exit.c
int		exit_builtin(char **args, t_env *envp);

//ft_echo.c
int		echo_builtin(char **args, t_env *envp);

//ft_unset.c
int		unset_builtin(char **args, t_env *envp);

//ft_export.c
int		export_builtin(char **args, t_env *envp);

#endif
