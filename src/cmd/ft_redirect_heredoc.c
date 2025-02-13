/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:28:12 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/13 18:45:42 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	free_aux_buffers(char *buffer, char *bf_trim)
{
	free(buffer);
	free(bf_trim);
}

static int	error_here_doc(char *msg, char *buffer, char *bf_trim)
{
	perror(msg);
	free_aux_buffers(buffer, bf_trim);
	return (-1);
}

static void	reset_next_round(char*buffer, char *bf_trim)
{
	free_aux_buffers(buffer, bf_trim);
	ft_printf(">");
}

static void	close_here_doc(int fdhd[2], char	*buffer, char *bf_trim)
{
	free_aux_buffers(buffer, bf_trim);
	close(fdhd[WRITE_END]);
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
		if (ft_pmatch_str(bf_trim, node->aux->key, ft_strlen(node->aux->key)) == 0)
		{
			(close_here_doc(fdhd, bf, bf_trim));
			break ;
		}
		if (write(fdhd[WRITE_END], bf, ft_strlen(bf)) != (ssize_t)ft_strlen(bf))
			return (error_here_doc("Error writing heredoc", bf, bf_trim));
		reset_next_round(bf, bf_trim);
	}
	if (dup2(fdhd[READ_END], STDIN_FILENO) == -1)
		return (ft_error("Error redirecting standard input.\n", 0), -1);
	env->redirect.is_red_in = 1;
	close(fdhd[READ_END]);
	return (0);
}
