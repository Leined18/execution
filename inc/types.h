#ifndef TYPES_H
# define TYPES_H

# include "mt.h"

# define BUILTINS 4

typedef struct s_env t_env;

typedef int (*t_builtin_func)(char **args, t_env *envp);

typedef struct s_builtin
{
	char *name;
	t_builtin_func func;
} t_builtin;

typedef struct s_env
{
	t_mt		*mt_env;
	int			num_env;
	t_mt		*path;
	t_builtin	builtins[BUILTINS];
}			t_env;


#endif