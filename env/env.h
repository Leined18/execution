#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "memtrack.h"

typedef struct s_env
{
	//t_list	*lst_env;
	t_mt	*mt_env;
	char	**path;
	int		num_env;
}			t_env;

void		print_array(char **array);
int			copy_envp(t_env **environ, char **envp);
int			ft_setenv(const char *name, const char *value, t_mt **envp);

#endif // ENV_H