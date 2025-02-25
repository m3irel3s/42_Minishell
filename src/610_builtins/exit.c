/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:22:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 14:04:45 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * ft_exit - Exit the shell with the current exit status.
 * @shell: The t_shell structure containing the current exit status.
 *
 * This function will first call ft_handle_eof to handle any necessary
 * cleanup before exiting. Afterwards, it calls ft_cleanup to free any
 * dynamically allocated memory, and clears the history using rl_clear_history.
 * Finally, it calls exit with the current exit status.
 */
void	ft_exit(t_shell *shell)
{
	ft_handle_eof(shell);
	ft_cleanup(shell);
	rl_clear_history();
	exit(g_exit_status);
}

/**
 * ft_handle_eof - Handle an end-of-file event.
 * @shell: The t_shell structure containing the shell's exit status.
 *
 * This function will print "exit\n" to the standard output, free the
 * dynamically allocated memory for the shell's environment variables,
 * and set the shell's exit status to EXIT_SUCCESS.
 */
void	ft_handle_eof(t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (shell->env_cpy)
		ft_free_arr(shell->env_cpy);
	g_exit_status = EXIT_SUCCESS;
}
