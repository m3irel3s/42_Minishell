/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/11 16:07:50 by meferraz         ###   ########.fr       */
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

/**
 * @brief Advances the pointer to the next command token in the linked list.
 *
 * @details
 * This function takes a pointer to a pointer to a token and advances it to
 * the next command in the linked list. If the token is a pipe, it will be
 * skipped and the pointer will be advanced to the next command.
 *
 * @param curr_cmd A pointer to a pointer to the current token.
 */
void	ft_advance_to_next_cmd(t_token **curr_cmd)
{
	while (*curr_cmd && (*curr_cmd)->type != PIPE)
		*curr_cmd = (*curr_cmd)->next;
	if (*curr_cmd)
		*curr_cmd = (*curr_cmd)->next;
}
