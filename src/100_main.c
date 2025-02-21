/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:54 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 16:44:34 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_exit_status;

static void	ft_process_input(t_shell *shell);

/**
 * Main entry point of the minishell program.
 *
 * This function takes care of initializing the shell, setting up signal
 * handlers, and entering the main loop, which processes user input and
 * executes commands.
 *
 * Parameters:
 * @param argc: The number of command line arguments passed to the program.
 *              This is ignored.
 * @param argv: The command line arguments passed to the program. This is
 *              ignored.
 * @param envp: The environment variables passed to the program.
 *
 * Returns:
 * An exit status that is used to determine the exit status of the program.
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_display_startup_banner();
	if (ft_set_up_signals() == ERROR)
		return (ft_print_error(ERR_SIGNAL_SETUP_FAIL), EXIT_FAILURE);
	if (ft_init_shell(&shell, envp) == ERROR)
		return (ft_print_error(ERR_SHELL_INIT_FAIL), EXIT_FAILURE);
	while (1)
	{
		shell.prompt = ft_set_prompt(&shell);
		shell.input = ft_safe_readline(&shell);
		if (shell.input == NULL)
		{
			ft_handle_eof(&shell);
			break ;
		}
		ft_process_input(&shell);
	}
	ft_cleanup(&shell);
	rl_clear_history();
	return (g_exit_status);
}

/**
 * @brief Process the input string from the user.
 *
 * This function takes the input string from the user and adds it to the
 * readline history. It then calls ft_parse_input to parse the input string
 * and ft_exec to execute the parsed commands. If the parsing is successful,
 * the exit status of the shell is set to SUCCESS; otherwise, it is set to
 * EXIT_FAILURE. Finally, it calls ft_cleanup to free any dynamically
 * allocated memory.
 *
 * @param shell A pointer to the shell structure containing the input string.
 */
static void	ft_process_input(t_shell *shell)
{
	if (*shell->input)
	{
		add_history(shell->input);
		if (ft_parse_input(shell) == SUCCESS)
			ft_exec(shell);
		else
			g_exit_status = EXIT_FAILURE;
	}
	ft_cleanup(shell);
}
