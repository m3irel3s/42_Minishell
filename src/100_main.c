/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:54 by jmeirele          #+#    #+#             */
/*   Updated: 2025/01/31 13:56:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell	shell;

	ft_display_startup_banner();
	//signal(SIGINT, ft_handle_sigint); // Set up signal handling for Ctrl+C
	//ft_init_shell(&shell, envp); 
	while (1)
	{
		shell.prompt = ft_set_prompt();
		shell.input = ft_safe_readline(prompt);
		if (*shell.input)
			add_history(shell.input);
		//if (ft_parse_input == SUCCESS)
		//	ft_execute_input(shell.input);
		//free(shell.prompt); ???
		//free(shell.input); ????
	}
	rl_clear_history();
	return (0);
}
