/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 08:20:35 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *ft_expanded_line(t_shell *shell, char *line);

void ft_redirect_heredoc(t_shell *shell, char *delimiter)
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
		line = ft_expanded_line(shell, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: error opening heredoc file\n", STDERR_FILENO);
		return ;
	}
	unlink(".heredoc");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static char	*ft_expanded_line(t_shell *shell, char *line)
{
	char	*expanded_line;
	char	*tmp;
	size_t		i;

	expanded_line = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = ft_handle_dollar(shell, line, &i);
			if(tmp)
			{
				expanded_line = ft_strjoin(expanded_line, tmp);
				free(tmp);
			}
		}
		else
			expanded_line = ft_process_char(expanded_line, line[i++]);
	}
	free(line);
	return (expanded_line);
}
