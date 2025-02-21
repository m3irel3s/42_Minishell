/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 20:49:23 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handle_exec(t_shell *shell, t_cmd_type cmd);
static void	ft_cleanup_fds(int original_stdin, int original_stdout, t_shell *shell);

/**
 * @brief Executes the command sequence stored in the shell's token list.
 *
 * This function validates the shell and its tokens before proceeding. It
 * checks for redirection list creation, handles piping if necessary, and
 * determines the command type to execute. The function is responsible for
 * error handling related to invalid shell structures, input, or redirection
 * failures.
 *
 * @param shell A pointer to the shell structure containing the command tokens.
 */

void	ft_exec(t_shell *shell)
{
	t_token		*curr;
	t_cmd_type	cmd;

	if (!shell || !shell->tokens)
	{
		ft_print_error(ERR_INVALID_SHELL_OR_INPUT);
		return ;
	}
	curr = shell->tokens;
	if (!curr->value)
		return ;
	if (ft_create_redirection_list(shell) != SUCCESS)
	{
		ft_print_error(ERR_REDIR_OPEN_FAIL);
		return ;
	}
	if (ft_has_pipes(shell) == SUCCESS)
	{
		ft_handle_pipes(shell);
		return ;
	}
	cmd = ft_get_cmd_type(curr->value);
	ft_handle_exec(shell, cmd);
}

/**
 * Handles the execution of a command by setting up necessary redirections.
 *
 * This function duplicates the original stdin and stdout file descriptors
 * and attempts to handle any redirections specified in the shell structure.
 * If redirections are successful, it executes the command and then restores
 * the original file descriptors. If any step fails, an appropriate error message
 * is printed and resources are cleaned up.
 *
 * @param shell The shell structure containing redirection and command information.
 * @param cmd The type of command to execute.
 */

static void	ft_handle_exec(t_shell *shell, t_cmd_type cmd)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (original_stdout == -1 || original_stdin == -1)
	{
		ft_print_error(ERR_DUP_FAIL);
		return ;
	}
	if (ft_handle_redirections(shell) != SUCCESS)
	{
		ft_print_error(ERR_INVALID_REDIRECT_TYPE);
		ft_cleanup_fds(original_stdin, original_stdout, shell);
		return ;
	}
	if (dup2(shell->redirected_stdin, STDIN_FILENO) == -1 ||
		dup2(shell->redirected_stdout, STDOUT_FILENO) == -1)
	{
		ft_print_error(ERR_DUP2_FAIL);
		ft_cleanup_fds(original_stdin, original_stdout, shell);
		return ;
	}
	ft_execute_command(shell, cmd);
	ft_cleanup_fds(original_stdin, original_stdout, shell);
}

/**
 * @brief Executes a command
 *
 * Executes a command based on the cmd argument.
 *
 * @param shell The shell object
 * @param cmd The command to execute
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
	else
		ft_print_error(ERR_CMD_NOT_FOUND);
}

/**
 * Determines the command type from a given command string.
 *
 * @param cmd The command string to evaluate.
 * @return The corresponding command type as an enum value of t_cmd_type.
 *         Returns CMD_UNKNOWN if the command is NULL or doesn't match any
 *         recognized command. If the command matches known shell built-in
 *         commands or "exec", it returns the appropriate t_cmd_type value.
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

/**
 * Restores the original file descriptors for stdin and stdout, and closes
 * the duplicated file descriptors as well as any redirected stdin and stdout
 * within the shell structure.
 *
 * @param original_stdin The original file descriptor for standard input.
 * @param original_stdout The original file descriptor for standard output.
 * @param shell The shell structure containing redirected stdin and stdout.
 */

static void	ft_cleanup_fds(int original_stdin, int original_stdout, t_shell *shell)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	close(shell->redirected_stdin);
	close(shell->redirected_stdout);
}
