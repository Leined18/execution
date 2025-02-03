#ifndef COMMANDS_H
# define COMMANDS_H

# define READ_END	0
# define WRITE_END	1

# include "types.h"
# include "libft.h"
# include "mt.h"

// Include any necessary headers here

// Declare your function prototypes here

typedef struct s_command
{
	char		*command;
	char		*cmd_path;
	char		**args;
}			t_command;

/* ************************************************************************** */
/*                                 COMMANDS                                   */
/* ************************************************************************** */

//execution.c
int			execute_tree(t_mt *node, t_env *env, int is_child);

//ft_create_cmd.c
t_command	*create_command(t_mt *parsed_cmd, t_env *envp);
void		print_command(t_command *cmd);

//ft_free_command.c
void		free_command(t_command *cmd);

//ft_get_cmd_path.c
char		*get_cmd_path(char **split_path, const char *cmd);

//ft_execmd.c
int			process_command(t_mt *node, t_env *env, int is_child);

//ft_assignation.c
int			ft_assignation(t_mt *node, t_env *envp);

//ft_expand.c
char		*ft_expand(char *str, int state, t_env *envp);

//ft_pipe_cmd.c
int			execute_pipe(t_mt *node, t_env *env);
int			update_last_status(int status);

//ft_redirect_input.c
void		redirect_input(t_mt *node, int open_mode);

//ft_redirect_output.c
void		redirect_output(t_mt *node, int open_mode);

void		create_child(t_command *cmd, int *pipefd, int child_num);
void		pipe_commands(t_command *cmd1, t_command *cmd2);
void		handle_parent(int *pipefd, pid_t pid1, pid_t pid2);
t_command	*parse_command(char *input, char **environ, t_list **lst);

#endif // COMMANDS_H