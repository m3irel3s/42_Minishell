/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 16:14:47 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute_input(t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		ft_putstr_fd("minishell: error duplicating file descriptors\n",
			STDERR_FILENO);
		return ;
	}
	ft_handle_redirections(shell);
	if (ft_strncmp(shell->tokens->value, "echo", 5) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->tokens->value, "cd", 3) == 0)
		ft_cd(shell);
	else if (ft_strncmp(shell->tokens->value, "env", 4) == 0)
		ft_env(shell);
	else if (ft_strncmp(shell->tokens->value, "pwd", 4) == SUCCESS)
		ft_pwd(shell);
	//else if (ft_strncmp(shell->tokens->value, "export", 7) == SUCCESS)
		//ft_export(shell);
	else if (ft_strncmp(shell->tokens->value, "exit", 5) == SUCCESS)
		ft_exit(shell);
	if (dup2(saved_stdin, STDIN_FILENO) == -1 ||
		dup2(saved_stdout, STDOUT_FILENO) == -1)
		ft_putstr_fd("minishell: error restoring file descriptors\n",
			STDERR_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}


