/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_misuse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:41:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 13:50:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints an error message to the standard error stream and sets the shell's
 * exit status to EXIT_MISUSE.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 *
 * @return Always returns EXIT_MISUSE, indicating that an error occurred.
 */
t_status	ft_print_error_misuse(t_shell *shell, char *error_msg)
{
	return (ft_print_error_custom_status(shell, error_msg, EXIT_MISUSE));
}

/**
 * Prints an error message to the standard error stream and sets the shell's
 * exit status to EXIT_INVALID_EXIT_ARG.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 *
 * @return Always returns EXIT_INVALID_EXIT_ARG, indicating that an error
 *         occurred.
 */
t_status	ft_print_error_invalid_exit_arg(t_shell *shell,
	char *error_msg)
{
	return (ft_print_error_custom_status(shell, error_msg,
			EXIT_INVALID_EXIT_ARG));
}
