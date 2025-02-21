/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_exit_failure.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:27:21 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 13:49:23 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints an error message to the standard error stream and sets the
 * shell's exit status to EXIT_FAILURE.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 * @return Always returns ERROR, indicating that an error occurred.
 */
t_status	ft_print_error(t_shell *shell, char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	if (shell)
		shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}

/**
 * @brief Prints an error message to the standard error stream and sets the
 * shell's exit status to a custom value.
 *
 * This function allows specifying a custom exit status, which is set in the
 * shell structure after printing the provided error message.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 * @param exit_status The custom exit status to set in the shell.
 * @return Always returns ERROR, indicating that an error occurred.
 */

t_status	ft_print_error_custom_status(t_shell *shell, char *error_msg,
	int exit_status)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	if (shell)
		shell->exit_status = exit_status;
	return (ERROR);
}

t_status	ft_print_syntax_error(t_shell *shell, char *token)
{
	if (!token)
		return (ft_print_error(shell, ERR_INVALID_PARAMS));

	ft_putstr_fd(ERR_SYNTAX_UNEXPECTED_TOKEN, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (shell)
		shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}

t_status	ft_print_unmatched_quote_error(t_shell *shell)
{
	return (ft_print_error(shell, ERR_SYNTAX_UNCLOSED_QUOTE));
}

t_status	ft_print_redirect_no_file_error(t_shell *shell)
{
	return (ft_print_error(shell, ERR_SYNTAX_EOF_REDIR));
}
