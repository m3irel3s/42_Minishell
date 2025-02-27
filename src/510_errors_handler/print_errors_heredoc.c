/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:30:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * Prints a heredoc delimiter error message to the standard error stream and
 * sets the shell's exit status to EXIT_FAILURE.
 *
 * This error occurs when a here-document is delimited by end-of-file without
 * encountering the expected delimiter.
 *
 * @param shell The shell structure to update the exit status.
 *
 * @return Always returns ERROR, indicating that an error occurred.
 */

t_status	ft_print_heredoc_delim_error(void)
{
	return (ft_print_error(ERR_SYNTAX_EOF_HEREDOC));
}
