/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_command_not_found.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:36:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Prints an error message for a command not found and sets the shell's
 *        exit status to EXIT_COMMAND_NOT_FOUND.
 *
 * This function checks if the provided command is valid, and if not, it calls
 * ft_print_error with an error message indicating invalid parameters. If the
 * command is valid, it prints the "command not found" error message to the
 * standard error stream, followed by the command name. Finally, it updates
 * the shell's exit status.
 *
 * @param shell The shell structure to update the exit status.
 * @param cmd The command that was not found.
 *
 * @return Always returns ERROR, indicating that a command not found error
 *         occurred.
 */
t_status	ft_print_command_not_found_error(char *cmd)
{
	if (!cmd)
		return (ft_print_error(ERR_INVALID_PARAMS));
	ft_printf(STDERR_FILENO, ERR_CMD_NOT_FOUND, cmd);
	g_exit_status = EXIT_COMMAND_NOT_FOUND;
	return (ERROR);
}
