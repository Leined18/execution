#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "mt.h"

typedef struct s_env
{
	t_mt	*mt_env;
	t_mt	*path;
	int		num_env;
}			t_env;

void	print_lst_data(t_mt *array);
int		copy_envp(t_env **environ, char **envp);
int		ft_setenv(const char *name, const char *value, t_mt *envp);
char	*ft_getenv(const char *name, t_mt *envp);
char	*ft_getenv_value(const char *name, t_mt *envp);

#endif // ENV_H