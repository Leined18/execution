#ifndef ENV_H
# define ENV_H

# include "libft.h"

typedef struct s_env
{
	t_list	*lst_env;
	char	**path;
	int		num_env;
}			t_env;

int			copy_envp(t_env **environ, char **envp);

#endif // ENV_H