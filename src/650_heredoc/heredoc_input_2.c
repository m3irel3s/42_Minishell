/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:19:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/12 15:52:25 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handle_expansion(t_shell *shell, char *line, int quoted, int fd);

/**
 * @brief Reads heredoc input from standard input and writes it to a file
 * descriptor.
 *
 * Reads input from standard input until the delimiter is found. If the delimiter
 * is found, the input loop is exited and the temporary file is closed. If the
 * input is not quoted, it is expanded before being written to the temporary
 * file.
 *
 * @param shell The shell structure containing relevant context.
 * @param delimiter The delimiter to signal the end of heredoc input.
 * @param quoted A flag indicating whether the input is quoted.
 * @param fd The file descriptor to write the heredoc input to.
 */
void	ft_read_heredoc_input(t_shell *shell, char *delimiter, int quoted,
		int fd)
{
	char	*line;

	rl_catch_signals = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_print_error_w_arg(ERR_EOF_HEREDOC, delimiter, EXIT_FAILURE);
			ft_cleanup_w_env(shell);
			close(fd);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_cleanup_w_env(shell);
			ft_free(line);
			close(fd);
			g_gbl.g_exit_status = EXIT_SUCCESS;
			exit(g_gbl.g_exit_status);
		}
		ft_handle_expansion(shell, line, quoted, fd);
	}
}

/**
 * @brief Handles the expansion of a heredoc input line.
 *
 * This function processes a heredoc input line by expanding any
 * environment variables if the line is not quoted. It writes the
 * (expanded) line to the specified file descriptor followed by a
 * newline character.
 *
 * @param shell The shell structure containing relevant context.
 * @param line The input line from the heredoc that may contain variables
 * to be expanded.
 * @param quoted A flag indicating whether the line is quoted, which
 * prevents expansion if true.
 * @param fd The file descriptor to which the processed line is written.
 */
static void	ft_handle_expansion(t_shell *shell, char *line, int quoted, int fd)
{
	char	*expanded_line;

	expanded_line = line;
	if (!quoted)
		expanded_line = ft_expanded_line(shell, line);
	write(fd, expanded_line, ft_strlen(expanded_line));
	write(fd, "\n", 1);
	ft_free(expanded_line);
}
