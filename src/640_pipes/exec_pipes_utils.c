/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 14:35:34 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Allocates and creates pipes for the given tokens.
 *
 * This function counts the number of pipe tokens in the linked list,
 * allocates memory for the pipes, and initializes them by creating
 * the necessary file descriptors.
 *
 * @param tokens The head of the linked list of tokens.
 * @return A pointer to the array of pipes or NULL if allocation fails
 *         or if a pipe could not be created.
 */

t_pipe	*ft_allocate_and_create_pipes(t_token *tokens)
{
	int		i;
	int		num_pipes;
	int		pipe_fds[2];
	t_pipe	*pipes;

	num_pipes = ft_count_pipes(tokens);
	pipes = ft_safe_calloc(sizeof(t_pipe) * num_pipes);
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

/**
 * @brief Counts the number of pipes in the linked list of tokens.
 *
 * @param tokens The head of the linked list of tokens.
 * @return The number of pipes in the linked list.
 */
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
