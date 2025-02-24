/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:45:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/24 10:32:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_apply_redirection(t_shell *shell, t_redirect *redirect);
static t_status	ft_redirect_in(t_redirect *redirect);
static t_status	ft_redirect_out(t_redirect *redirect);
static t_status	ft_redirect_append(t_redirect *redirect);

/**
 * @brief Handles the redirections specified in the shell structure.
 *
 * This function saves the current standard input and output file descriptors,
 * then iterates through the linked list of redirections in the shell structure,
 * applying each redirection in sequence. After applying the redirections, it
 * updates the shell's redirected stdin and stdout to reflect the current state
 * of the standard input and output. Finally, it restores the original standard
 * input and output before returning.
 *
 * @param shell A pointer to the shell structure containing the redirections.
 * @return t_status SUCCESS if all redirections were successfully handled, ERROR
 * otherwise.
 */

t_status	ft_handle_redirections(t_shell *shell)
{
	t_redirect	*redirect;
	int			saved_stdin;
	int			saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (ft_print_error(ERR_DUP_FAIL));
	redirect = shell->redirects;
	while (redirect)
	{
		if (ft_apply_redirection(shell, redirect) != SUCCESS)
			return (ERROR);
		redirect = redirect->next;
	}
	shell->redirected_stdin = dup(STDIN_FILENO);
	shell->redirected_stdout = dup(STDOUT_FILENO);
	if (shell->redirected_stdin == -1 || shell->redirected_stdout == -1)
		return (ft_print_error(ERR_DUP_FAIL));
	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
			STDOUT_FILENO) == -1)
		return (ft_print_error(ERR_DUP2_FAIL));
	close(saved_stdin);
	close(saved_stdout);
	return (SUCCESS);
}

/**
 * @brief Applies a redirection to the shell's standard input or output.
 *
 * This function takes a redirection structure and applies it to the shell's
 * standard input or output by calling the appropriate redirection function.
 * If the redirection type is not recognized, it prints an error message and
 * returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the redirection.
 * @param redirect A pointer to the redirection structure to be applied.
 * @return t_status SUCCESS if the redirection was successfully applied,
 * ERROR otherwise.
 */
static t_status	ft_apply_redirection(t_shell *shell, t_redirect *redirect)
{
	if (redirect->type == REDIRECT_IN)
		return (ft_redirect_in(redirect));
	else if (redirect->type == REDIRECT_OUT)
		return (ft_redirect_out(redirect));
	else if (redirect->type == REDIRECT_APPEND)
		return (ft_redirect_append(redirect));
	else if (redirect->type == HEREDOC)
		return (ft_redirect_heredoc(shell, redirect));
	return (ft_print_error(ERR_INVALID_REDIRECT_TYPE));
}

/**
 * @brief Redirects the standard input to a file.
 *
 * This function opens the file associated with the given redirection structure
 * and sets it as the standard input of the shell. If the file does not exist,
 * it prints an error message and returns ERROR. If the file cannot be opened,
 * it prints an appropriate error message and returns ERROR. If the file is
 * successfully opened, it duplicates the file descriptor and sets it as the
 * standard input, and then closes the original file descriptor. If the
 * duplication fails, it prints an error message and returns ERROR.
 *
 * @param redirect A pointer to the redirection structure containing the
 * filename associated with the redirection.
 * @return t_status SUCCESS if the redirection was successfully applied,
 * ERROR otherwise.
 */
static t_status	ft_redirect_in(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			return (ft_print_error(ft_format_error(ERR_REDIR_NO_FILE,
						redirect->filename)));
		else if (errno == EACCES)
			return (ft_print_error(ft_format_error(ERR_REDIR_PERM_DENIED,
						redirect->filename)));
		else
			return (ft_print_error(ft_format_error(ERR_REDIR_OPEN_FAIL,
						redirect->filename)));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ft_print_error(ERR_DUP2_FAIL));
	}
	close(fd);
	return (SUCCESS);
}

/**
 * Opens the file associated with the given redirection structure and sets it
 * as the standard output of the shell. If the file does not exist, it is
 * created. If the file cannot be opened, it prints an appropriate error
 * message and returns ERROR. If the file is successfully opened, it
 * duplicates the file descriptor and sets it as the standard output, and then
 * closes the original file descriptor. If the duplication fails, it prints an
 * error message and returns ERROR.
 *
 * @param redirect A pointer to the redirection structure containing the
 * filename associated with the redirection.
 * @return t_status SUCCESS if the redirection was successfully applied,
 * ERROR otherwise.
 */
static t_status	ft_redirect_out(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (ft_print_error(ft_format_error(ERR_REDIR_PERM_DENIED,
						redirect->filename)));
		else if (errno == EISDIR)
			return (ft_print_error(ft_format_error(ERR_REDIR_IS_DIR,
						redirect->filename)));
		else
			return (ft_print_error(ft_format_error(ERR_REDIR_OPEN_FAIL,
						redirect->filename)));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_print_error(ERR_DUP2_FAIL));
	}
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Redirects the standard output to a file in append mode.
 *
 * This function opens the file associated with the given redirection structure
 * in append mode and sets it as the standard output of the shell. If the file
 * does not exist, it is created. If the file cannot be opened, it prints an
 * appropriate error message and returns ERROR. If the file is successfully
 * opened, it duplicates the file descriptor and sets it as the standard output,
 * and then closes the original file descriptor. If the duplication fails, it
 * prints an error message and returns ERROR.
 *
 * @param redirect A pointer to the redirection structure containing the
 * filename associated with the redirection.
 * @return t_status SUCCESS if the redirection was successfully applied,
 * ERROR otherwise.
 */
static t_status	ft_redirect_append(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (ft_print_error(ft_format_error(ERR_REDIR_PERM_DENIED,
						redirect->filename)));
		else if (errno == EISDIR)
			return (ft_print_error(ft_format_error(ERR_REDIR_IS_DIR,
						redirect->filename)));
		else
			return (ft_print_error(ft_format_error(ERR_REDIR_OPEN_FAIL,
						redirect->filename)));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_print_error(ERR_DUP2_FAIL));
	}
	close(fd);
	return (SUCCESS);
}
