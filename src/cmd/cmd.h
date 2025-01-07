#ifndef COMMANDS_H
# define COMMANDS_H

# include "types.h"
# include "libft.h"
# include "mt.h"

// Include any necessary headers here

// Declare your function prototypes here

typedef struct s_command
{
	char	*command;
	char	*cmd_path;
	char	**args;
}			t_command;

/* ************************************************************************** */
/*                                 COMMANDS                                   */
/* ************************************************************************** */

//ft_create_cmd.c
t_command	*create_command(t_mt *parsed_cmd, char **path);
void		print_command(t_command *cmd);

//ft_free_command.c
void		free_command(t_command *cmd);

//ft_get_cmd_path.c
char		*get_cmd_path(char **split_path, const char *cmd);

//ft_execmd.c
int			execution(t_command *cmd, t_env *envp);
void		exec_command(t_command *cmd, char **env);

//ft_assignation.c
int			ft_assignation(t_command *cmd, t_env *envp);


void		redirect_output(int fd);
void		redirect_input(int fd);
void		create_child(t_command *cmd, int *pipefd, int child_num);
void		pipe_commands(t_command *cmd1, t_command *cmd2);
void		handle_parent(int *pipefd, pid_t pid1, pid_t pid2);
t_command	*parse_command(char *input, char **environ, t_list **lst);

/* // Builtin functions
int			execute_builtin(t_command *cmd);
int			execute_external(t_command *cmd);
int			execute_pipe(t_command *cmd);
int			execute_redirection(t_command *cmd);
int			execute_semicolon(t_command *cmd);
int	execute_tree(t_command *cmd); */

#endif // COMMANDS_H