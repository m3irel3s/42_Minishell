/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_expanded_line(t_shell *shell, char *line);

/**
 * @brief Redirects the input from a heredoc to the standard input of a command.
 *
 * This function sets up a pipe, reads lines from the user with readline, and
 * writes the lines to the pipe after optionally expanding variables in the
 * line. The pipe is then set as the standard input of the command.
 *
 * @param shell A pointer to the shell structure containing the redirection.
 * @param redirect A pointer to the redirection structure containing the
 * filename associated with the heredoc delimiter.
 * @return t_status SUCCESS if the heredoc was successfully set up, ERROR otherwise.
 */
t_status	ft_redirect_heredoc(t_shell *shell, t_redirect *redirect)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (ft_print_error(ERR_PIPE_FAIL));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redirect->filename) == 0)
		{
			free(line);
			break ;
		}
		if (!redirect->quoted)
			line = ft_expanded_line(shell, line);
		if (write(fd[1], line, ft_strlen(line)) == -1 ||
			write(fd[1], "\n", 1) == -1)
		{
			free(line);
			close(fd[1]);
			close(fd[0]);
			return (ft_print_error(ERR_WRITE_FAIL));
		}
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		return (ft_print_error(ERR_DUP2_FAIL));
	}
	close(fd[0]);
	return (SUCCESS);
}

/**
 * @brief Expands a line of input by replacing '$' characters with their values.
 *
 * This function iterates through the input line, replacing any '$' characters
 * with their expanded values using ft_handle_dollar. The expanded line is then
 * returned.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param line The input line to be expanded.
 * @return The expanded line as a string.
 */
static char	*ft_expanded_line(t_shell *shell, char *line)
{
	char	*expanded_line;
	char	*tmp;
	size_t	i;

	expanded_line = ft_safe_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = ft_handle_dollar(shell, line, &i);
			if (tmp)
			{
				expanded_line = ft_safe_strjoin(expanded_line, tmp, 0);
				free(tmp);
			}
		}
		else
			expanded_line = ft_process_char(expanded_line, line[i++]);
	}
	free(line);
	return (expanded_line);
}
