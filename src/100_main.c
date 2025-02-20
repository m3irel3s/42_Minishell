/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:54 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 14:13:25 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_process_input(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_display_startup_banner();
	if (ft_set_up_signals() == ERROR)
	{
		ft_printf(STDERR_FILENO, ERR_SIGNAL_SETUP_FAIL);
		return (EXIT_FAILURE);
	}
	if (ft_init_shell(&shell, envp) == ERROR)
	{
		ft_printf(STDERR_FILENO, ERR_SHELL_INIT_FAIL);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		shell.prompt = ft_set_prompt();
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
	return (shell.exit_status);
}

static void	ft_process_input(t_shell *shell)
{
	if (*shell->input)
	{
		add_history(shell->input);
		if (ft_parse_input(shell) == SUCCESS)
			ft_exec(shell);
		else
			shell->exit_status = EXIT_FAILURE;
	}
	ft_cleanup(shell);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:54 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 14:45:00 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_process_input(t_shell *shell);
static void	ft_handle_eof(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_display_startup_banner();
	if (ft_set_up_signals() == ERROR)
	{
		ft_printf(STDERR_FILENO, ERR_SIGNAL_SETUP_FAIL);
		return (EXIT_FAILURE);
	}
	if (ft_init_shell(&shell, envp) == ERROR)
	{
		ft_printf(STDERR_FILENO, ERR_SHELL_INIT_FAIL);
		return (EXIT_FAILURE);
	}
	shell.exit_status = EXIT_SUCCESS;
	while (1)
	{
		shell.prompt = ft_set_prompt();
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
	return (shell.exit_status);
}

static void	ft_process_input(t_shell *shell)
{
	if (*shell->input)
	{
		add_history(shell->input);
		if (ft_parse_input(shell) == SUCCESS)
			ft_exec(shell);
		else
			shell->exit_status = EXIT_FAILURE;
	}
	ft_cleanup(shell);
}
