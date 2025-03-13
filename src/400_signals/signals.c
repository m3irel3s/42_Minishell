/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:56:30 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 17:38:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_sigint(int sig);

/**
 * @brief Sets up signal handlers for SIGINT and SIGQUIT
 *
 * This function sets up two signal handlers. The first handles SIGINT and is
 * responsible for printing a new line and prompting the user again. The second
 * handles SIGQUIT and is currently empty, but can be used to add extra
 * functionality.
 */
t_status	ft_set_up_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = ft_handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (ft_print_error(ERR_SIGNAL_SETUP_INT), ERROR);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (ft_print_error(ERR_SIGNAL_SETUP_QUIT), ERROR);
	return (SUCCESS);
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
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = EXIT_SIGINT;
}

/**
 * @brief Set up SIGINT to be ignored in parent.
 *
 * This function configures a sigaction structure to ignore SIGINT signals,
 * saves the old action for SIGINT, and sets the new action.
 *
 * @param sa_ignore Structure to hold the new action.
 * @param sa_old Structure to hold the old action.
 * @return SUCCESS if the sigaction call was successful, ERROR otherwise.
 */
t_status	ft_setup_sigint_ignore(struct sigaction *sa_ignore,
	struct sigaction *sa_old)
{
	sa_ignore->sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore->sa_mask);
	sa_ignore->sa_flags = 0;
	if (sigaction(SIGINT, sa_ignore, sa_old) == -1)
		return (ft_print_error("sigaction failed"), ERROR);
	return (SUCCESS);
}
