/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:15:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 16:19:54 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief The child process for heredoc.
 *
 * This function is executed by a child process created by
 * ft_handle_single_heredoc.
 * It sets up a signal handler for SIGINT to be the default handler, so that the
 * child process can be interrupted by a SIGINT signal (such as when the user
 * presses Ctrl+C).
 * It then opens the temporary file for writing, reads the heredoc input, writes
 * it to the file, and closes the file descriptor.
 * If the file cannot be opened, it prints an error message and exits with a
 * non-zero status.
 * If the file can be opened but there is an error while writing to it, it closes
 * the file descriptor and exits with a non-zero status.
 * If the file can be opened and written to successfully, it exits with a zero
 * status.
 *
 * @param shell The shell structure.
 * @param delim The delimiter token.
 * @param tempfile The temporary file name.
 */
static void	ft_child_heredoc(t_shell *shell, t_token *delim, char *tempfile)
{
	struct sigaction	sa;
	int					fd;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(ERR_OPEN_FAIL);
		ft_free(tempfile);
		exit(EXIT_FAILURE);
	}
	ft_read_heredoc_input(shell, delim->val.value, delim->quoted, fd);
	close(fd);
	exit(EXIT_SUCCESS);
}

/**
 * Reads input from the user and writes it to the given file descriptor until
 * it encounters the given delimiter.
 * If the delimiter is not encountered and the user reaches the end of the file
 * (EOF), it prints an error message to the standard error stream and exits.
 * If the delimiter is not quoted, it expands the variables in the input
 * according to the shell's environment.
 *
 * @param shell The shell structure.
 * @param delimiter The delimiter string.
 * @param quoted A flag indicating whether the delimiter is quoted or not.
 * @param fd The file descriptor to write to.
 */
void	ft_read_heredoc_input(t_shell *shell, char *delimiter, int quoted, int fd)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(STDERR_FILENO, ERR_EOF_HEREDOC, delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_free(line);
			break ;
		}
		expanded_line = line;
		if (!quoted)
			expanded_line = ft_expanded_line(shell, line);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		ft_free(expanded_line);
	}
}

/**
 * Expands the given line by expanding any variables starting with '$'.
 *
 * This function works by iterating over the line and checking for the '$'
 * character. If it finds it, it calls ft_handle_dollar to expand the variable
 * and appends the expanded value to the expanded line. If it does not find a '$'
 * character, it simply appends the current character to the expanded line.
 * If memory allocation fails, the function sets the shell's exit status to
 * failure and returns NULL.
 *
 * @param shell The shell structure containing the environment.
 * @param line The line to be expanded.
 * @return The expanded line, or NULL if there is a memory allocation failure.
 */
static char	*ft_expanded_line(t_shell *shell, char *line)
{
	char	*expanded;
	char	*tmp;
	size_t	i;

	expanded = ft_safe_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = ft_handle_dollar(shell, line, &i);
			if (tmp)
			{
				expanded = ft_safe_strjoin(expanded, tmp, 0);
				free(tmp);
			}
		}
		else
			expanded = ft_process_char(expanded, line[i++]);
	}
	ft_free(line);
	return (expanded);
}
