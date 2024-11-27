#ifndef BUILTINS_H
# define BUILTINS_H

// Include any necessary headers here

# include "env.h"
# include "libft.h"

typedef int (*t_builtin_func)(char **args, t_env *envp);

typedef struct s_builtin
{
	char *name;
	t_builtin_func func;
} t_builtin;

//ft_cd.c
//int		cd_builtin(char *path, t_env *envp);
int		cd_builtin(char **args, t_env *envp);

//ft_env.c
//int		env_builtin(t_mt **first);
int		env_builtin(char **args, t_env *envp);
void	print_array(char **array);

//ft_pwd.c
int	    pwd_builtin(t_mt *mt_env);

#endif // BUILTINS_H