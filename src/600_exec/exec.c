/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 10:23:35 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handle_exec(t_shell *shell, int cmd);

/**
 * @brief Executes a command in a shell.
 *
 * @details
 * This function takes a shell structure and executes the command given in the
 * tokens linked list. If there are pipes, it calls ft_handle_pipes to handle
 * them. Otherwise, it calls ft_handle_exec to execute the command.
 *
 * @param [in] shell The shell structure to execute the command in.
 */
void	ft_exec(t_shell *shell)
{
	t_token		*curr;
	t_cmd_type	cmd;

	curr = shell->tokens;
	if (!curr || !curr->value)
		return ;
	ft_create_redirection_list(shell);
	// t_redirect	*redirects = shell->redirects;
	// while (redirects)
	// {
	// 	printf("type: %d\n", redirects->type);
	// 	printf("filename: %s\n", redirects->filename);
	// 	printf("quoted: %d\n", redirects->quoted);
	// 	redirects = redirects->next;
	// }
	// ft_printf(1, "--------------------\n");
	// t_token		*tokens = shell->tokens;
	// while (tokens)
	// {
	// 	printf("value: %s\n", tokens->value);
	// 	printf("type: %d\n", tokens->type);
	// 	printf("quoted: %d\n", tokens->quoted);
	// 	tokens = tokens->next;
	// }
	if (ft_has_pipes(shell) == SUCCESS)
	{
		ft_handle_pipes(shell);
		return ;
	}
	cmd = ft_get_cmd_type(curr->value);
	ft_handle_exec(shell, cmd);
}

/**
 * @brief Handle the execution of a command and its redirections.
 *
 * @param shell The shell structure.
 * @param cmd The type of command to be executed.
 *
 * This function is responsible for executing a command and its redirections.
 * It duplicates the standard input and output file descriptors, applies the
 * redirections in the shell redirection list, executes the command, and then
 * restores the original standard input and output file descriptors.
 *
 * It also closes the duplicated and redirected file descriptors.
 */
static void	ft_handle_exec(t_shell *shell, int cmd)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	ft_handle_redirections(shell);
	dup2(shell->redirected_stdin, STDIN_FILENO);
	dup2(shell->redirected_stdout, STDOUT_FILENO);
	ft_execute_command(shell, cmd);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	close(shell->redirected_stdin);
	close(shell->redirected_stdout);
}

/**
 * @brief Execute the given command.
 *
 * @param shell The shell structure.
 * @param cmd The type of command to be executed.
 *
 * This function takes a command type as argument and execute the corresponding
 * command. If the command is CMD_EXEC, it will execute the command given as
 * argument. For other commands, it will call the corresponding function.
 */
void	ft_execute_command(t_shell *shell, t_cmd_type cmd)
{
	if (cmd == CMD_EXEC)
		ft_execute_cmd(shell, shell->tokens->value);
	else if (cmd == CMD_AUTHORS)
		ft_authors();
	else if (cmd == CMD_ECHO)
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
}

/**
 * @brief Determine the type of the command.
 *
 * @param cmd The command to identify.
 * @return The type of the command.
 *
 * This function takes a command as a string and returns the corresponding
 * enum value. If the command is not a valid command, CMD_UNKNOWN is returned.
 */
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
