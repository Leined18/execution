#ifndef BUILTINS_H
# define BUILTINS_H

// Include any necessary headers here

# include "env.h"
# include "libft.h"

int		cd_builtin(char *path, t_env ***envp);
void	env_builtin(char **env);

#endif // BUILTINS_H