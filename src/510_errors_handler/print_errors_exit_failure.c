/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_exit_failure.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:27:21 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/14 17:13:03 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Prints an error message to the standard error stream and sets the
 * shell's exit status to EXIT_FAILURE.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 * @return Always returns ERROR, indicating that an error occurred.
 */
t_status	ft_print_error(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	g_exit_status = EXIT_FAILURE;
	return (ERROR);
}

/**
 * @brief Prints an error message when a syntax error is encountered in the
 * input string, and sets the shell's exit status to EXIT_FAILURE.
 *
 * This function prints an error message to the standard error stream when a
 * syntax error is encountered while parsing the input string. The error
 * message is constructed by formatting the ERR_SYNTAX_UNEXPECTED_TOKEN
 * message with the token that caused the error. The shell's exit status is
 * set to EXIT_FAILURE after printing the error message.
 *
 * @param token The token that caused the syntax error.
 * @return Always returns ERROR, indicating that an error occurred.
 */
t_status	ft_print_syntax_error(char *token)
{
	if (!token)
		return (ft_print_error(ERR_INVALID_PARAMS));
	ft_printf(STDERR_FILENO, ERR_SYNTAX_UNEXPECTED_TOKEN, token);
	g_exit_status = EXIT_FAILURE;
	return (ERROR);
}

/**
 * @brief Prints an error message to the standard error stream and sets the
 * shell's exit status to EXIT_FAILURE when an unmatched quote is encountered
 * in the input string.
 *
 * This function is used when a syntax error is encountered while parsing the
 * input string, and no matching quote is found for a quoted string. The error
 * message is constructed by formatting the ERR_SYNTAX_UNCLOSED_QUOTE message
 * with the line number where the error occurred. The shell's exit status is
 * set to EXIT_FAILURE after printing the error message.
 *
 * @return Always returns ERROR, indicating that an error occurred.
 */
t_status	ft_print_unmatched_quote_error(void)
{
	return (ft_print_error(ERR_SYNTAX_UNCLOSED_QUOTE));
}

/**
 * @brief Prints an error message when a redirection is encountered at the end
 * of the input string, and sets the shell's exit status to EXIT_FAILURE.
 *
 * This function prints an error message to the standard error stream when a
 * redirection is encountered at the end of the input string, and sets the
 * shell's exit status to EXIT_FAILURE. The error message is constructed by
 * formatting the ERR_SYNTAX_EOF_REDIR message. The shell's exit status is set
 * to EXIT_FAILURE after printing the error message.
 *
 * @return Always returns ERROR, indicating that an error occurred.
 */
t_status	ft_print_redirect_no_file_error(void)
{
	return (ft_print_error(ERR_SYNTAX_EOF_REDIR));
}
