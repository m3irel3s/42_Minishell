/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/01 16:54:01 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*ft_allocate_and_create_pipes(t_token *tokens)
{
	int		i;
	int		num_pipes;
	int		pipe_fds[2];
	t_pipe	*pipes;

	num_pipes = ft_count_pipes(tokens);
	pipes = ft_safe_malloc(sizeof(t_pipe) * num_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fds) == -1)
		{
			ft_print_error(ERR_PIPE_FAIL);
			free(pipes);
			return (NULL);
		}
		pipes[i].read_fd = pipe_fds[0];
		pipes[i].write_fd = pipe_fds[1];
		i++;
	}
	return (pipes);
}

int	ft_count_pipes(t_token *tokens)
{
	int	counter;

	counter = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			counter++;
		tokens = tokens->next;
	}
	return (counter);
}

void	ft_advance_to_next_cmd(t_token **curr_cmd)
{
	while (*curr_cmd && (*curr_cmd)->type != PIPE)
		*curr_cmd = (*curr_cmd)->next;
	if (*curr_cmd)
		*curr_cmd = (*curr_cmd)->next;
}
