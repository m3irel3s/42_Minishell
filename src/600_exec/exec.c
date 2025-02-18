/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 09:30:04 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handle_exec(t_shell *shell)
{
	t_token		*curr;
	t_cmd_type	cmd;

	curr = shell->tokens;
	if (!curr || !curr->value)
		return ;
	cmd = ft_get_cmd_type(curr->value);
	// if (cmd == CMD_EXEC)
	// 	ft_execute_external(shell);
	if (cmd == CMD_ECHO)
		ft_echo(shell);
	else if (cmd == CMD_CD)
		ft_cd(shell);
	else if (cmd == CMD_PWD)
		ft_pwd(shell);
	else if (cmd == CMD_EXPORT)
		ft_export(shell);
	else if (cmd == CMD_ENV)
		ft_env(shell);
	else if (cmd == CMD_EXIT)
		ft_exit(shell);
	else if (cmd == CMD_UNSET)
		ft_unset(shell);
	else
		ft_print_command_not_found_error(curr->value);
}
void	ft_execute_input(t_shell *shell)
{
	ft_handle_exec(shell);
	// int	saved_stdin;
	// int	saved_stdout;

	// saved_stdin = dup(STDIN_FILENO);
	// saved_stdout = dup(STDOUT_FILENO);
	// if (saved_stdin == -1 || saved_stdout == -1)
	// {
	// 	ft_putstr_fd("minishell: error duplicating file descriptors\n", STDERR_FILENO);
	// 	return ;
	// }

	// ft_handle_redirections(shell);

	// if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout, STDOUT_FILENO) == -1)
		// ft_putstr_fd("minishell: error restoring file descriptors\n", STDERR_FILENO);
	//
	// close(saved_stdin);
	// close(saved_stdout);
}

t_cmd_type	ft_get_cmd_type(char *cmd)
{
	if (!cmd)
		return (CMD_UNKNOWN);
	if (ft_strcmp(cmd, "echo") == SUCCESS)
		return (CMD_ECHO);
	if (ft_strcmp(cmd, "cd") == SUCCESS)
		return (CMD_CD);
	if (ft_strcmp(cmd, "pwd") == SUCCESS)
		return (CMD_PWD);
	if (ft_strcmp(cmd, "export") == SUCCESS)
		return (CMD_EXPORT);
	if (ft_strcmp(cmd, "unset") == SUCCESS)
		return (CMD_UNSET);
	if (ft_strcmp(cmd, "env") == SUCCESS)
		return (CMD_ENV);
	if (ft_strcmp(cmd, "exit") == SUCCESS)
		return (CMD_EXIT);
	return (CMD_EXEC);
}


