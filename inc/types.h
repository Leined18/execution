#ifndef TYPES_H
# define TYPES_H

# include "mt.h"
# include "cmd.h"

# define BUILTINS 8

typedef struct s_env t_env;

typedef int (*t_builtin_func)(t_command *cmd, t_env *envp);

typedef struct s_builtin
{
	char *name;
	t_builtin_func func;
} t_builtin;

typedef struct s_env
{
	t_mt		*mt_env;
	int			num_env;
	t_mt		*mt_var;
	int			num_var;
	char		**path;
	t_builtin	builtins[BUILTINS];
}			t_env;

#endif