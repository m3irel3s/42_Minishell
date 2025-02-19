/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:45:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/19 13:47:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_apply_redirection(t_redirect *redirect);
static void	ft_redirect_in(t_redirect *redirect);
static void	ft_redirect_out(t_redirect *redirect);
static void	ft_redirect_append(t_redirect *redirect);

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
		ft_apply_redirection(redirect);
		redirect = redirect->next;
	}
	shell->redirected_stdin = dup(STDIN_FILENO);
	shell->redirected_stdout = dup(STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	ft_apply_redirection(t_redirect *redirect)
{
	if (redirect->type == REDIRECT_IN)
		ft_redirect_in(redirect);
	else if (redirect->type == REDIRECT_OUT)
		ft_redirect_out(redirect);
	else if (redirect->type == REDIRECT_APPEND)
		ft_redirect_append(redirect);
	else if (redirect->type == HEREDOC)
		ft_redirect_heredoc(redirect->filename);
}

static void ft_redirect_in(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
		return;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void ft_redirect_out(t_redirect *redirect)
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

static void ft_redirect_append(t_redirect *redirect)
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
