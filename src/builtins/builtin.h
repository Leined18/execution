#ifndef BUILTIN_H
# define BUILTIN_H

// Include any necessary headers here

# include "libft.h"
# include "types.h"
#include "cmd.h"

//builtin.h
void init_builtins(t_builtin *builtins);
int execute_builtin(t_command *cmd, t_env *envp);

//ft_cd.c
int		cd_builtin(t_command *cmd, t_env *envp);

//ft_env.c
int		env_builtin(t_command *cmd, t_env *envp);

//ft_pwd.c
int		pwd_builtin(t_command *cmd, t_env *envp);

//ft_exit.c
int		exit_builtin(t_command *cmd, t_env *envp);

//ft_echo.c
int		echo_builtin(t_command *cmd, t_env *envp);

//ft_unset.c
int		unset_builtin(t_command *cmd, t_env *envp);

//ft_export.c
int		export_builtin(t_command *cmd, t_env *envp);

#endif
