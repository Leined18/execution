/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:28:12 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/26 11:56:38 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static int	error_here_doc(char *msg, char *buffer, char *bf_trim, t_env *env)
{
	perror(msg);
	free(buffer);
	free(bf_trim);
	return (env->last_status = 1, 1);
}

static void	reset_next_round(char*buffer, char *bf_trim)
{
	free(buffer);
	free(bf_trim);
	ft_printf(">");
}

static void	close_here_doc(int fdhd[2], char	*buffer, char *bf_trim)
{
	free(buffer);
	free(bf_trim);
	close(fdhd[WRITE_END]);
}

static int	duplicate_heredoc_stdin(int fdhd[2], t_env *env)
{
	if (dup2(fdhd[READ_END], STDIN_FILENO) == -1)
		return (ft_error("Error redirecting standard input.\n", 0), -1);
	env->redirect.is_red_in = 1;
	close(fdhd[READ_END]);
	return (env->last_status = 0, 0);
}

int	redirect_heredoc(t_mt *node, t_env *env)
{
	int		fdhd[2];
	char	*bf;
	char	*bf_trim;

	if (pipe(fdhd) == -1)
		return (-1);
	ft_printf(">");
	while (1)
	{
		bf = get_next_line(STDIN_FILENO);
		if (!bf)
			continue ;
		bf_trim = ft_strtrim(bf, "\n");
		if (!ft_pmatch_str(bf_trim, node->aux->key, ft_strlen(node->aux->key)))
		{
			(close_here_doc(fdhd, bf, bf_trim));
			break ;
		}
		if (write(fdhd[WRITE_END], bf, ft_strlen(bf)) != (ssize_t)ft_strlen(bf))
			return (error_here_doc("Error writing heredoc", bf, bf_trim, env));
		reset_next_round(bf, bf_trim);
	}
	return (duplicate_heredoc_stdin(fdhd, env));
}
