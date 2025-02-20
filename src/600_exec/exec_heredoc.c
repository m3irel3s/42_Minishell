/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 11:04:05 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *ft_expanded_line(t_shell *shell, char *line);

void ft_redirect_heredoc(t_shell *shell, t_redirect *redirect)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("minishell: error creating heredoc pipe\n", STDERR_FILENO);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redirect->filename) == 0)
		{
			free(line);
			break ;
		}
		if (!redirect->quoted)
			line = ft_expanded_line(shell, line);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
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
