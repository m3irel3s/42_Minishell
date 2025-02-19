/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/19 15:54:49 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	ft_exec(t_shell *shell)
{
	t_token		*curr;
	t_cmd_type	cmd;

	curr = shell->tokens;

	if (!curr || !curr->value)
		return ;
	ft_create_redirection_list(shell);
	if (ft_has_pipes(shell) == SUCCESS)
	{
		ft_handle_pipes(shell);
		return ;
	}
	cmd = ft_get_cmd_type(curr->value);
	ft_handle_exec(shell, cmd);
}

void	ft_handle_exec(t_shell *shell, int cmd)
{
	int original_stdout = dup(STDOUT_FILENO);
	int original_stdin = dup(STDIN_FILENO);

	ft_handle_redirections(shell);
	dup2(shell->redirected_stdin, STDIN_FILENO);
	dup2(shell->redirected_stdout, STDOUT_FILENO);
	if (cmd == CMD_EXEC)
		ft_execute_cmd(shell, shell->tokens->value);
	if (cmd == CMD_AUTHORS)
		ft_authors();
	else if
	 (cmd == CMD_ECHO)
		ft_echo(shell);
	else if (cmd == CMD_CD)
		ft_cd(shell);
	else if (cmd == CMD_PWD)
		ft_pwd();
	else if (cmd == CMD_EXPORT)
		ft_export(shell);
	else if (cmd == CMD_ENV)
		ft_env(shell);
	else if (cmd == CMD_EXIT)
		ft_exit(shell);
	else if (cmd == CMD_UNSET)
		ft_unset(shell);
	// else
	// 	ft_print_command_not_found_error(shell->tokens->value);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	close(shell->redirected_stdin);
	close(shell->redirected_stdout);
}

t_cmd_type	ft_get_cmd_type(char *cmd)
{
	if (!cmd)
		return (CMD_UNKNOWN);
	if (ft_strcmp(cmd, "authors") == SUCCESS)
		return (CMD_AUTHORS);
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

