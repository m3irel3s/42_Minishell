/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:48:40 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/01 17:03:59 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cleanup_pipes(t_pipe *pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i].read_fd);
		close(pipes[i].write_fd);
		i++;
	}
}

void	ft_close_child_pipes(t_pipe *pipes, int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j].read_fd);
		close(pipes[j].write_fd);
		j++;
	}
}

void	ft_free_redirects(t_redirect *redirects)
{
	t_redirect	*tmp;

	while (redirects)
	{
		tmp = redirects;
		redirects = redirects->next;
		free(tmp->filename);
		free(tmp);
	}
}
