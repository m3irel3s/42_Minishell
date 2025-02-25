/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:45:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/25 11:02:12 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_apply_redirection(t_shell *shell, t_redirect *redirect);
static void	ft_redirect_in(t_redirect *redirect);
static void	ft_redirect_out(t_redirect *redirect);
static void	ft_redirect_append(t_redirect *redirect);

/**
 * @brief Handles redirections for the shell.
 *
 * This function takes a shell structure and applies all redirections in the
 * shell's redirection list. It saves the original standard input and output
 * file descriptors, applies each redirection in the list, and then restores
 * the original standard input and output file descriptors. The redirections
 * are applied in the order in which they appear in the redirection list.
 *
 * @param shell A pointer to the shell structure containing the redirection
 *              list.
 */
void	ft_handle_redirections(t_shell *shell)
{
	t_redirect	*redirect;
	int			saved_stdin;
	int			saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redirect = shell->redirects;
	while (redirect)
	{
		ft_apply_redirection(shell, redirect);
		redirect = redirect->next;
	}
	shell->redirected_stdin = dup(STDIN_FILENO);
	shell->redirected_stdout = dup(STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

/**
 * @brief Applies a redirection to the shell's standard input and/or output.
 *
 * This function takes a redirection structure and applies the redirection
 * to the shell's standard input and/or output. The type of redirection is
 * determined by the redirect->type field. If the type is REDIRECT_IN,
 * the redirection is applied using ft_redirect_in. If the type is
 * REDIRECT_OUT, the redirection is applied using ft_redirect_out. If the
 * type is REDIRECT_APPEND, the redirection is applied using
 * ft_redirect_append. If the type is HEREDOC, the redirection is applied
 * using ft_redirect_heredoc.
 *
 * @param shell A pointer to the shell structure to which the redirection is
 *              to be applied.
 * @param redirect A pointer to the redirection structure containing the
 *                 redirection to be applied.
 */
static void	ft_apply_redirection(t_shell *shell, t_redirect *redirect)
{
	if (redirect->type == REDIRECT_IN)
		ft_redirect_in(redirect);
	else if (redirect->type == REDIRECT_OUT)
		ft_redirect_out(redirect);
	else if (redirect->type == REDIRECT_APPEND)
		ft_redirect_append(redirect);
	else if (redirect->type == HEREDOC)
		ft_redirect_heredoc(shell, redirect);
}

/**
 * @brief Opens a file for reading and redirects the standard input to it.
 *
 * This function attempts to open the file specified by the `redirect`
 * structure's filename in read-only mode. If the file is successfully opened,
 * it redirects the standard input (STDIN) to this file. In case of a failure
 * to open the file, an error message is printed to the standard error.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 filename for the input redirection.
 */

static void	ft_redirect_in(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/**
 * @brief Opens a file in overwrite mode and redirects the standard output to it.
 *
 * This function attempts to open the file specified by the `redirect`
 * structure's filename in write-only and overwrite mode. If the file does not
 * exist, it is created with the permissions set to 0644. If the file is
 * successfully opened, it redirects the standard output (STDOUT) to this file.
 * In case of a failure to open the file, an error message is printed to
 * the standard error.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 filename for the overwrite operation.
 */
static void	ft_redirect_out(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/**
 * @brief Opens a file in append mode and redirects the standard output to it.
 *
 * This function attempts to open the file specified by the `redirect`
 * structure's filename in write-only and append mode. If the file does not
 * exist, it is created with the permissions set to 0644. If the file is
 * successfully opened, it redirects the standard output (STDOUT) to this file.
 * In case of a failure to open the file, an error message is printed to
 * the standard error.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 filename for the append operation.
 */

static void	ft_redirect_append(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
