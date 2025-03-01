/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:43:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/27 17:12:29 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_wait_for_children(int num_children);

/**
 * @brief Handles the execution of commands with pipes in the shell.
 *
 * This function manages the creation and management of pipes between
 * commands in a command sequence. It allocates the necessary pipes,
 * forks child processes for each command, and executes them with the
 * appropriate pipe redirections. It also handles errors related to pipe
 * creation and forking. After the commands are executed, it waits for
 * all child processes to complete, cleans up the pipes, and frees
 * allocated resources.
 *
 * @param shell A pointer to the shell structure containing the command tokens.
 */
void ft_handle_pipes(t_shell *shell)
{
	int num_pipes;
	t_pipe *pipes;
	t_token *curr_cmd;
	pid_t pid;
	int i;

	num_pipes = ft_count_pipes(shell->tokens);
	pipes = ft_allocate_and_create_pipes(shell->tokens);
	if (!pipes)
	{
		ft_print_error(ERR_PIPE_FAIL);
		return;
	}
	curr_cmd = shell->tokens;
	i = 0;
	while (i < num_pipes + 1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_execute_child(shell, curr_cmd, i, pipes, num_pipes);
			exit(g_exit_status);
		}
		else if (pid < 0)
		{
			ft_print_error(ERR_FORK_FAIL);
			ft_cleanup_pipes(pipes, num_pipes);
			free(pipes);
			return;
		}
		ft_advance_to_next_cmd(&curr_cmd);
		i++;
	}
	ft_cleanup_pipes(pipes, num_pipes);
	ft_wait_for_children(num_pipes + 1);
	free(pipes);
}

/**
 * @brief Waits for all child processes to complete.
 *
 * This function waits for all the child processes created by ft_handle_pipes to
 * complete. It uses the wait system call to wait for each child process to
 * finish, and then stores the exit status of the last child process in the
 * global variable g_exit_status. If any of the child processes finish with an
 * exit status of 0, it sets g_exit_status to EXIT_SUCCESS. Otherwise, it sets
 * g_exit_status to EXIT_FAILURE.
 *
 * @param num_children The number of child processes to wait for.
 */
static void	ft_wait_for_children(int num_children)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_children)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}
