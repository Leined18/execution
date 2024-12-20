#ifndef EXE_UTILS_H
# define EXE_UTILS_H

# include "exe.h"

//arra2d_utils.c
int		free_array2d(char **array);
size_t	array2d_len(char **array);
void	print_array2d(char **array);
char	**mtconvert_array2d(t_mt *list);

//tmlst_utils.c.c
void	print_lst_data(t_mt *array);
void	ft_mtdel_one(t_mt **first, t_mt *node);
t_mt	*ft_mtpop_one(t_mt **first, char* find);

#endif