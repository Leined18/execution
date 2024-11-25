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
int 	ft_find_env(const char *s1, const char *s2, size_t n);
//LUEGO CAMBIAR
char	*ft_strrtrim(char const *s1, char const *set);
char	*ft_strltrim(char const *s1, char const *set);

#endif // ENV_H