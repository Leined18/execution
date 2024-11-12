#ifndef BUILTINS_H
# define BUILTINS_H

// Include any necessary headers here

# include "env.h"
# include "libft.h"

int		cd_builtin(char *path, t_env *envp);
void	env_builtin(t_list **first);
void	print_array(char **array);

#endif // BUILTINS_H