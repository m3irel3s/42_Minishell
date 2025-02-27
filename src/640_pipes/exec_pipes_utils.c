/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Allocate and create pipes based on the number of pipes in the token list.
 *
 * @param tokens The token list to count the number of pipes from.
 * @return A pointer to an array of t_pipe structures, each containing two file descriptors for a pipe.
 */
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

/**
 * @brief Counts the number of pipe tokens in a linked list of tokens.
 *
 * This function iterates through the given list of tokens and counts
 * how many of them are of type PIPE. It returns the total count of
 * such tokens found in the list.
 *
 * @param tokens A pointer to the head of the linked list of tokens.
 * @return The number of pipe tokens in the list.
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
 * @brief Closes all the pipes in the given array.
 *
 * @param pipes The array of pipes to be closed.
 * @param num_pipes The number of pipes in the array.
 */
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

/**
 * @brief Advances the current command pointer to the next command.
 *
 * This function moves the current command pointer to the token following
 * the next PIPE token, effectively advancing to the start of the next
 * command in the token list. If the current command is already at the end
 * of the list or there are no more PIPE tokens, the pointer is set to NULL.
 *
 * @param curr_cmd A double pointer to the current command token.
 */

void	ft_advance_to_next_cmd(t_token **curr_cmd)
{
	while (*curr_cmd && (*curr_cmd)->type != PIPE)
		*curr_cmd = (*curr_cmd)->next;
	if (*curr_cmd)
		*curr_cmd = (*curr_cmd)->next;
}
