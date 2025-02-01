/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:56:30 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/01 10:28:51 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	ft_handle_sigint(int sig);

/**
 * Sets up signal handling for the shell.
 *
 * This function sets up the signal handlers for the shell. It registers
 * a handler for SIGINT (Ctrl+C) that refreshes the prompt on a new line
 * without exiting the shell. It also sets SIGQUIT (Ctrl+\) to be ignored.
 */
void	ft_set_up_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Handles the SIGINT signal (Ctrl+C) during the shell's execution.
 *
 * This function is called when the SIGINT signal is received. It performs
 * the necessary actions to refresh the prompt on a new line without exiting
 * the shell. Specifically, it writes a newline character, updates the 
 * Readline library's internal state, clears the current input line, and
 * redisplays the prompt.
 *
 * @param sig The signal number (unused in this function).
 */

static void	ft_handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
