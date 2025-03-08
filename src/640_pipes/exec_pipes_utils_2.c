/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:48:40 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 14:36:52 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Closes all the read and write file descriptors of the pipes given.
 *
 * @details
 * This function takes a t_pipe structure and the number of pipes to close, and
 * iterates through the structure, closing all the read and write file
 * descriptors of each pipe.
 *
 * @param [in] pipes The t_pipe structure containing the pipes to close.
 * @param [in] num_pipes The number of pipes to close.
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
 * @brief Closes all the read and write file descriptors of the pipes given,
 * excluding the one for the current process.
 *
 * @details
 * This function takes a t_pipe structure and the number of pipes to close, and
 * iterates through the structure, closing all the read and write file
 * descriptors of each pipe, except for the last one, which is the current
 * process.
 *
 * @param [in] pipes The t_pipe structure containing the pipes to close.
 * @param [in] num_pipes The number of pipes to close.
 */
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

/**
 * @brief Frees a linked list of redirection structures.
 *
 * @details
 * This function iterates through a linked list of t_redirect structures,
 * freeing the memory associated with each structure's filename and the
 * structure itself.
 *
 * @param [in] redirects A pointer to the head of the redirection linked list.
 */

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
