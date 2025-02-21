/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:27:21 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 08:19:38 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints an error message if an unmatched quote is found.
 *
 * This function prints ERR_SYNTAX_UNCLOSED_QUOTE to the standard error stream
 * and sets the shell's exit status to EXIT_FAILURE.
 *
 * @param shell The shell struct to update the exit status.
 *
 * @return Returns ERROR, indicating that an error was found.
 */
t_status	ft_print_unmatched_quote_error(t_shell *shell)
{
	ft_putstr_fd(ERR_SYNTAX_UNCLOSED_QUOTE, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}


/**
 * @brief Prints an error message for an unexpected token in the syntax.
 *
 * If the given token is NULL, prints ERR_INVALID_PARAMS to the standard error
 * stream and sets the shell's exit status to EXIT_FAILURE.
 *
 * Otherwise, prints ERR_SYNTAX_UNEXPECTED_TOKEN to the standard error stream,
 * formatting it with the unexpected token, and sets the shell's exit status to
 * EXIT_FAILURE.
 *
 * @param shell The shell struct to update the exit status.
 * @param token The unexpected token.
 *
 * @return Returns ERROR, indicating that an error was found.
 */
t_status	ft_print_syntax_error(t_shell *shell, char *token)
{
	if (!token)
	{
		ft_putstr_fd(ERR_INVALID_PARAMS, STDERR_FILENO);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	ft_printf(STDERR_FILENO, ERR_SYNTAX_UNEXPECTED_TOKEN, token);
	shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}

/**
 * @brief Prints an error message when a redirection operator is not followed by
 *        a filename.
 *
 * Prints ERR_SYNTAX_EOF_REDIR to the standard error stream and sets the shell's
 * exit status to EXIT_FAILURE.
 *
 * @param shell The shell struct to update the exit status.
 *
 * @return Returns ERROR, indicating that an error was found.
 */
t_status	ft_print_redirect_no_file_error(t_shell *shell)
{
	ft_putstr_fd(ERR_SYNTAX_EOF_REDIR, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}

/**
 * @brief Prints an error message when a command is not found.
 *
 * If the command is NULL, it prints ERR_INVALID_PARAMS to the standard error
 * stream and sets the shell's exit status to EXIT_FAILURE. Otherwise, it
 * formats and prints ERR_CMD_NOT_FOUND with the command name, setting the
 * exit status to EXIT_COMMAND_NOT_FOUND.
 *
 * @param shell The shell struct to update the exit status.
 * @param cmd The command that was not found.
 *
 * @return Returns ERROR, indicating that an error was found.
 */

t_status	ft_print_command_not_found_error(t_shell *shell, char *cmd)
{
	if (!cmd)
	{
		ft_putstr_fd(ERR_INVALID_PARAMS, STDERR_FILENO);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	ft_printf(STDERR_FILENO, ERR_CMD_NOT_FOUND, cmd);
	shell->exit_status = EXIT_COMMAND_NOT_FOUND;
	return (ERROR);
}

t_status	ft_print_heredoc_delim_error(t_shell *shell)
{
	ft_putstr_fd(ERR_SYNTAX_EOF_HEREDOC, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}
