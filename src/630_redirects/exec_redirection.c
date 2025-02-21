/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:45:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 15:25:36 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_apply_redirection(t_shell *shell, t_redirect *redirect);
static t_status	ft_redirect_in(t_shell *shell, t_redirect *redirect);
static t_status	ft_redirect_out(t_shell *shell, t_redirect *redirect);
static t_status	ft_redirect_append(t_shell *shell, t_redirect *redirect);

t_status	ft_handle_redirections(t_shell *shell)
{
	t_redirect	*redirect;
	int			saved_stdin;
	int			saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (ft_print_error(shell, ERR_DUP_FAIL));
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
		return (ft_print_error(shell, ERR_DUP_FAIL));
	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
			STDOUT_FILENO) == -1)
		return (ft_print_error(shell, ERR_DUP2_FAIL));
	close(saved_stdin);
	close(saved_stdout);
	return (SUCCESS);
}

static t_status	ft_apply_redirection(t_shell *shell, t_redirect *redirect)
{
	if (redirect->type == REDIRECT_IN)
		return (ft_redirect_in(shell, redirect));
	else if (redirect->type == REDIRECT_OUT)
		return (ft_redirect_out(shell, redirect));
	else if (redirect->type == REDIRECT_APPEND)
		return (ft_redirect_append(shell, redirect));
	else if (redirect->type == HEREDOC)
		return (ft_redirect_heredoc(shell, redirect));
	return (ft_print_error(shell, ERR_INVALID_REDIRECT_TYPE));
}

static t_status	ft_redirect_in(t_shell *shell, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_NO_FILE,
						redirect->filename)));
		else if (errno == EACCES)
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_PERM_DENIED,
						redirect->filename)));
		else
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_OPEN_FAIL,
						redirect->filename)));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ft_print_error(shell, ERR_DUP2_FAIL));
	}
	close(fd);
	return (SUCCESS);
}

static t_status	ft_redirect_out(t_shell *shell, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_PERM_DENIED,
						redirect->filename)));
		else if (errno == EISDIR)
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_IS_DIR,
						redirect->filename)));
		else
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_OPEN_FAIL,
						redirect->filename)));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_print_error(shell, ERR_DUP2_FAIL));
	}
	close(fd);
	return (SUCCESS);
}

static t_status	ft_redirect_append(t_shell *shell, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_PERM_DENIED,
						redirect->filename)));
		else if (errno == EISDIR)
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_IS_DIR,
						redirect->filename)));
		else
			return (ft_print_error(shell, ft_format_error(ERR_REDIR_OPEN_FAIL,
						redirect->filename)));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_print_error(shell, ERR_DUP2_FAIL));
	}
	close(fd);
	return (SUCCESS);
}
