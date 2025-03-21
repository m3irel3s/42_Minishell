/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:48:40 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/17 17:11:16 by meferraz         ###   ########.fr       */
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
void	ft_close_child_pipes(t_pipe *pipes, int *pids, int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j].read_fd);
		close(pipes[j].write_fd);
		j++;
	}
	ft_free(pipes);
	ft_free(pids);
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

/**
 * @brief Cleans up the shell structure and exits with EXIT_FAILURE.
 *
 * This function is used when an error occurs during the execution of a command
 * or when an exit status is not explicitly set. It cleans up the shell
 * structure by freeing the dynamically allocated memory associated with the
 * tokens, redirects, temporary files, and environment variables, and then
 * exits the shell with the status EXIT_FAILURE.
 *
 * @param [in] sh The shell structure to clean up and exit.
 */
void	ft_clean_and_exit(t_shell *sh)
{
	ft_cleanup_w_env(sh);
	g_exit_status = EXIT_FAILURE;
	exit(g_exit_status);
}

/**
 * @brief Cleans up the shell structure and frees the temporary files array.
 *
 * @details
 * This function is used when a pipe command is executed in a child process.
 * It cleans up the shell structure by freeing the dynamically allocated memory
 * associated with the tokens, redirects, temporary files, and environment
 * variables, and then exits the child process.
 *
 * @param [in] shell The shell structure to clean up.
 */
void	ft_clean_pipe_child(t_shell *shell)
{
	ft_cleanup_w_env(shell);
	ft_free_arr(shell->temp_files);
}
