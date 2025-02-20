/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:22:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 14:12:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(t_shell *shell)
{
	ft_handle_eof(shell);
	ft_cleanup(shell);
	rl_clear_history();
	exit(shell->exit_status);
}
void	ft_handle_eof(t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (shell->env_cpy)
		ft_free_arr(shell->env_cpy);
	shell->exit_status = EXIT_SUCCESS;
}
