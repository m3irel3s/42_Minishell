/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 21:37:13 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Checks the syntax of a heredoc operator.
 *
 * Checks if the next token is a word or a quoted token. If it is not, it prints
 * a syntax error message and sets the exit status to EXIT_FAILURE.
 *
 * @param current The token containing the heredoc operator.
 * @return ERROR if the syntax is invalid, SUCCESS otherwise.
 */
t_status	ft_check_heredoc_syntax(t_token *current)
{
	if (!current->next || (current->next->type != WORD
			&& !current->next->quoted))
		return (ft_print_syntax_error("newline"), ERROR);
	return (SUCCESS);
}

/**
 * @brief Handles the exit status of a child process after reading a heredoc
 * input.
 *
 * If the child process exited with a non-zero status, it unlinks the temporary
 * file, frees the dynamically allocated memory for the temporary file name,
 * sets the shell's exit status to the child's exit status, and returns ERROR.
 * Otherwise, it returns SUCCESS.
 *
 * @param status The exit status of the child process.
 * @param tempfile The name of the temporary file.
 * @return ERROR if the child process exited with a non-zero status, SUCCESS
 * otherwise.
 */
t_status ft_handle_child_exit(int status, char *tempfile)
{
    int exit_code;

    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);

        // Always unlink tempfile regardless of exit code
        unlink(tempfile);
        ft_free(tempfile);

        if (exit_code == 130) {  // SIGINT
            ft_printf(STDOUT_FILENO, "^C\n");
            g_exit_status = exit_code;
            return ERROR;
        }
        else if (exit_code != EXIT_SUCCESS) {  // EOF
            ft_print_error_w_arg(ERR_EOF_HEREDOC, "heredoc", exit_code);
            g_exit_status = exit_code;
            return ERROR;
        }
    }
    return SUCCESS;
}

/**
 * @brief Handles the signal status of a child process after reading a heredoc
 * input.
 *
 * If the child process was interrupted by a signal, it unlinks the temporary
 * file, frees the dynamically allocated memory for the temporary file name,
 * sets the shell's exit status to EXIT_FAILURE, prints a new line, and returns
 * ERROR. Otherwise, it returns SUCCESS.
 *
 * @param status The signal status of the child process.
 * @param tempfile The name of the temporary file.
 * @return ERROR if the child process was interrupted by a signal, SUCCESS
 * otherwise.
 */
t_status	ft_handle_child_signal(int status, char *tempfile)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(tempfile);
		ft_free(tempfile);
		g_exit_status = EXIT_FAILURE;
		write(STDOUT_FILENO, "\n", 1);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Process all heredoc redirections in the shell's token list.
 *
 * Saves the current standard input, processes each heredoc redirection in the
 * shell's token list by calling ft_handle_single_heredoc, and restores the
 * original standard input after all heredocs have been processed.
 *
 * @param shell The shell structure containing the token list.
 * @return SUCCESS if all heredoc redirections were processed
 * successfully, ERROR otherwise.
 */
t_status	ft_process_heredocs(t_shell *shell)
{
	t_token	*current;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (ERROR);
	current = shell->tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (ft_handle_single_heredoc(shell, current) == ERROR)
			{
				if (dup2(saved_stdin, STDIN_FILENO) == -1)
					ft_print_error(ERR_DUP2_FAIL);
				close(saved_stdin);
				return (ERROR);
			}
		}
		current = current->next;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		ft_print_error(ERR_DUP2_FAIL);
	close(saved_stdin);
	return (SUCCESS);
}
