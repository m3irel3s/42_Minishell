/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_fatal_signal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:46:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 13:49:13 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints an error message for a fatal signal and sets the shell's
 *        exit status accordingly.
 *
 * This function uses the provided error message and signal number to
 * construct an exit status value, which is then used to update the shell's
 * exit status. It leverages the ft_print_error_custom_status function for
 * the actual printing and status setting.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 * @param signal_number The signal number that caused the fatal error.
 *
 * @return Returns the status from ft_print_error_custom_status, which
 *         indicates the result of the error handling operation.
 */

t_status	ft_print_error_fatal_signal(t_shell *shell, char *error_msg,
		int signal_number)
{
	return (ft_print_error_custom_status(shell, error_msg,
			EXIT_FATAL_SIGNAL + signal_number));
}
