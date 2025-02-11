/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:54 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 15:01:18 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * Main entry point of the program.
 *
 * This function contains the main loop of the minishell program. It first
 * displays the startup banner, sets up the signal handlers and initializes
 * the shell structure. Then, it enters an infinite loop where it displays
 * the shell prompt, reads a line of input from the user, parses the line,
 * executes the parsed commands and frees the allocated memory. If the user
 * enters "exit", the loop is broken and the function returns an exit status.
 *
 * @param argc The number of command line arguments passed to the program.
 * @param argv An array of command line arguments passed to the program.
 * @param envp An array of environment variables passed to the program.
 *
 * @return An exit status of the program. If the user enters "exit", it
 *         returns SUCCESS (0). Otherwise, it returns FAILURE (1).
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_display_startup_banner();
	ft_set_up_signals();
	ft_init_shell(&shell, envp);
	while (1)
	{
		shell.prompt = ft_set_prompt();
		shell.input = ft_safe_readline(&shell);
		if (shell.input == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*shell.input)
			add_history(shell.input);
		if (ft_parse_input(&shell) == SUCCESS)
			ft_execute_input(&shell);
		ft_cleanup(&shell);
	}
	ft_cleanup(&shell);
	return (rl_clear_history(), SUCCESS);
}
