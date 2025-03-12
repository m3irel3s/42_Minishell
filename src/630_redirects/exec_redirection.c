/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:45:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/12 15:14:58 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status	ft_redirect_in(t_redirect *redirect);
static t_status	ft_redirect_out(t_redirect *redirect);
static t_status	ft_redirect_append(t_redirect *redirect);

/**
 * @brief Applies all redirections for the current shell command.
 *
 * Iterates through the shell's redirection list and applies each
 * redirection using the appropriate redirection function.
 *
 * @param shell A pointer to the shell structure containing the
 *              redirection list.
 * @return SUCCESS if all redirections are successful, otherwise ERROR.
 */
t_status	ft_handle_redirections(t_shell *shell)
{
	t_redirect	*redirect;
	int			saved_stdin;
	int			saved_stdout;
	t_status	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redirect = shell->redirects;
	status = SUCCESS;
	while (redirect)
	{
		if (ft_apply_redirection(redirect) == ERROR)
			status = ERROR;
		redirect = redirect->next;
	}
	shell->redirected_stdin = dup(STDIN_FILENO);
	shell->redirected_stdout = dup(STDOUT_FILENO);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		ft_print_error_and_status(&status);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		ft_print_error_and_status(&status);
	close(saved_stdin);
	close(saved_stdout);
	return (close(saved_stdin), close(saved_stdout), status);
}

/**
 * @brief Applies the specified redirection.
 *
 * This function checks the type of the given redirection and applies the
 * appropriate redirection operation. It supports input, output, and append
 * redirections. If the redirection type is not recognized, it returns
 * immediately without performing any redirection.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 redirection type and associated data.
 * @return A status indicating the success or failure of the redirection
 *         operation.
 */
t_status	ft_apply_redirection(t_redirect *redirect)
{
	if (redirect->type == REDIRECT_IN)
		return (ft_redirect_in(redirect));
	else if (redirect->type == REDIRECT_OUT)
		return (ft_redirect_out(redirect));
	else if (redirect->type == REDIRECT_APPEND)
		return (ft_redirect_append(redirect));
	return (SUCCESS);
}

/**
 * @brief Opens a file for reading and redirects the standard input to it.
 *
 * This function attempts to open the file specified by the `redirect` structure
 * in read-only mode. If the file is successfully opened, it duplicates the
 * file descriptor to the standard input. If any operation fails, an error
 * message is printed and the function returns ERROR.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 filename for input redirection.
 * @return SUCCESS if the redirection is successful, otherwise ERROR.
 */
static t_status	ft_redirect_in(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error_w_arg(ERR_REDIR_NO_FILE, redirect->filename,
			EXIT_FAILURE);
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_print_error(ERR_DUP2_FAIL);
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Opens a file for writing and redirects the standard output to it.
 *
 * This function attempts to open the file specified by the `redirect` structure
 * in write-only mode. If the file does not exist, it is created with the
 * permissions set to 0644. If the file is successfully opened, the file
 * descriptor is duplicated to the standard output. In case of a failure to
 * open the file or duplicate the file descriptor, an error message is printed
 * and the function returns ERROR.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 filename for output redirection.
 * @return SUCCESS if the redirection is successful, otherwise ERROR.
 */
static t_status	ft_redirect_out(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_print_error_w_arg(ERR_REDIR_NO_FILE, redirect->filename,
			EXIT_FAILURE);
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_print_error(ERR_DUP2_FAIL);
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Opens a file for writing and redirects the standard output to it,
 *        appending to the file if it already exists.
 *
 * This function attempts to open the file specified by the `redirect` structure
 * in write-only mode. If the file does not exist, it is created with the
 * permissions set to 0644. If the file is successfully opened, the file
 * descriptor is duplicated to the standard output. If the file already exists,
 * the file is opened in append mode and the output is appended to the end of
 * the file. In case of a failure to open the file or duplicate the file
 * descriptor, an error message is printed and the function returns ERROR.
 *
 * @param redirect A pointer to the redirection structure containing the
 *                 filename for output redirection.
 * @return SUCCESS if the redirection is successful, otherwise ERROR.
 */
static t_status	ft_redirect_append(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_print_error_w_arg(ERR_REDIR_NO_FILE, redirect->filename,
			EXIT_FAILURE);
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_print_error(ERR_DUP2_FAIL);
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}
