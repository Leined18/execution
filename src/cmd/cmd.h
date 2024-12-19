#ifndef COMMANDS_H
# define COMMANDS_H

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

t_command	*create_command(t_mt *parsed_cmd, char **path);
void		free_command(t_command *cmd);
void	print_command(t_command *cmd);

void		execute_command(t_command *cmd);
void		redirect_output(int fd);
void		redirect_input(int fd);
void		create_child(t_command *cmd, int *pipefd, int child_num);
void		pipe_commands(t_command *cmd1, t_command *cmd2);
void		handle_parent(int *pipefd, pid_t pid1, pid_t pid2);
char		*get_cmd_path(char *cmd, char **envp);
t_command	*parse_command(char *input, char **environ, t_list **lst);

/* // Builtin functions
int			execute_builtin(t_command *cmd);
int			execute_external(t_command *cmd);
int			execute_pipe(t_command *cmd);
int			execute_redirection(t_command *cmd);
int			execute_semicolon(t_command *cmd);
int	execute_tree(t_command *cmd); */

#endif // COMMANDS_H