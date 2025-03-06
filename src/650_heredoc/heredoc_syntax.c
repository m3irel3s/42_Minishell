/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 16:33:30 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Checks if the syntax of the heredoc token is valid.
 *
 * Checks if the heredoc token is immediately followed by a WORD token or a
 * quoted token. If not, prints an error message and sets the exit status to
 * EXIT_FAILURE.
 *
 * @param current The current token to be checked.
 * @return 1 if the syntax is invalid, 0 otherwise.
 */
static int	ft_check_heredoc_syntax(t_token *current)
{
	if (!current->next || (current->next->type != WORD && !current->next->quoted))
	{
		ft_print_syntax_error("newline");
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

/**
 * @brief Handles the exit status of a child process.
 *
 * If the child process exited normally but with a non-zero status,
 * this function unlinks and frees the tempfile, updates the global
 * exit status to the child's exit status, and returns 1.
 * Otherwise, it returns 0.
 *
 * @param status The status of the child process.
 * @param tempfile The name of the temporary file to be removed.
 * @return 1 if the child exited with a non-zero status, 0 otherwise.
 */

static int	ft_handle_child_exit(int status, char *tempfile)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		unlink(tempfile);
		ft_free(tempfile);
		g_exit_status = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}

/**
 * @brief Handles the signal termination of a child process.
 *
 * If the child process was terminated by a signal and the signal was
 * SIGINT, this function unlinks and frees the tempfile, updates the global

 * exit status to EXIT_FAILURE, writes a newline to the standard output, and
 * returns 1. Otherwise, it returns 0.
 *
 * @param status The status of the child process.
 * @param tempfile The name of the temporary file to be removed.
 * @return 1 if the child was terminated by SIGINT, 0 otherwise.
 */
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(tempfile);
		ft_free(tempfile);
		g_exit_status = EXIT_FAILURE;
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}


/**
 * @brief Handles all heredocs in the input.
 *
 * This function goes through all the tokens in the input and checks if
 * they are heredoc tokens. If they are, it calls ft_handle_single_heredoc
 * to handle the individual heredocs. If ft_handle_single_heredoc returns
 * ERROR, ft_process_heredocs returns after restoring the original STDIN
 * file descriptor.
 */
void	ft_process_heredocs(t_shell *shell)
{
	t_token	*current;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	current = shell->tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (ft_handle_single_heredoc(shell, current) == ERROR)
			{
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
				return ;
			}
		}
		current = current->next;
	}
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}
