/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:45:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/19 12:32:31 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_apply_redirection(t_redirect *redirect);
static void ft_redirect_heredoc(char *delimiter);

void	ft_handle_redirections(t_shell *shell)
{
	t_redirect	*redirect;

	redirect = shell->redirects;
	while (redirect)
	{
		ft_apply_redirection(redirect);
		redirect = redirect->next;
	}
}

static void	ft_apply_redirection(t_redirect *redirect)
{
	int	fd;
	int	target_fd;

	fd = -1;
	target_fd = STDOUT_FILENO;
	if (redirect->type == REDIRECT_IN)
	{
		fd = open(redirect->filename, O_RDONLY);
		target_fd = STDIN_FILENO;
	}
	else if (redirect->type == REDIRECT_OUT)
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == REDIRECT_APPEND)
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == HEREDOC)
		return (ft_redirect_heredoc(redirect->filename));
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
		return ;
	}
	if (dup2(fd, target_fd) == -1)
	{
		ft_printf(STDERR_FILENO, ERR_REDIR_AMBIGUOUS, redirect->filename);
		return ;
	}
	close(fd);
}

static void	ft_redirect_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: error creating heredoc file\n", STDERR_FILENO);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}
