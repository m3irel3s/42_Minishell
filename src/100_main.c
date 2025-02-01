/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:54 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/01 09:51:14 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * Main entry point for the minishell program.
 *
 * This function displays the startup banner, sets up signal handling,
 * initializes the shell structure, and enters an infinite loop to
 * repeatedly read and execute user input. It also cleans up any
 * dynamically allocated memory when the program exits.
 *
 * @param argc The number of command-line arguments provided.
 * @param argv An array of command-line arguments.
 * @param envp An array of environment variables.
 *
 * @return An integer indicating the program's exit status.
 *         (Currently always returns SUCCESS (0).)
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)envp;
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
		//if (ft_parse_input == SUCCESS)
		//	ft_execute_input(shell.input);
		free(shell.prompt);
		free(shell.input);
	}
	ft_cleanup(&shell);
	return (SUCCESS);
}
