/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:43:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/17 17:25:12 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_wait_for_children(pid_t *pids, int num_children);
static pid_t	ft_fork_exec(t_shell *sh, t_token *curr_cmd, t_pipe_util *p);

/**
 * @brief Handles a shell command that contains pipes.
 *
 * @details
 * This function takes a shell structure and executes the command given in the
 * tokens linked list. It allocates and creates a pipe for each pipe token in
 * the list, forks a new process for each command, and then waits for all the
 * children to finish before returning.
 *
 * @param [in] shell The shell structure to execute the command in.
 */
void	ft_handle_pipes(t_shell *shell)
{
	t_token		*curr_cmd;
	t_pipe_util	p;

	p.pipes = ft_allocate_and_create_pipes(shell->tokens);
	if (!p.pipes)
	{
		ft_print_error(ERR_PIPE_FAIL);
		return ;
	}
	p.pids = ft_safe_calloc(sizeof(pid_t)
			* (ft_count_pipes(shell->tokens) + 1));
	curr_cmd = shell->tokens;
	p.i = 0;
	while (p.i < ft_count_pipes(shell->tokens) + 1)
	{
		p.pids[p.i] = ft_fork_exec(shell, curr_cmd, &p);
		ft_advance_to_next_cmd(&curr_cmd);
		p.i++;
	}
	ft_cleanup_pipes(p.pipes, ft_count_pipes(shell->tokens));
	ft_wait_for_children(p.pids, ft_count_pipes(shell->tokens) + 1);
	ft_free(p.pipes);
	ft_free(p.pids);
}

/**
 * @brief Forks a new process for a single command in a pipe.
 *
 * @details
 * This function forks a new process and executes the given command in it.
 * If the fork fails, it prints an error message and exits.
 *
 * @param [in] sh The shell structure to execute the command in.
 * @param [in] curr_cmd The current command token.
 * @param [in] pipes The pipes structure.
 * @param [in] i The index of the current command.
 */
static pid_t	ft_fork_exec(t_shell *sh, t_token *curr_cmd, t_pipe_util *p)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_execute_child(sh, curr_cmd, p);
		exit(g_exit_status);
	}
	else if (pid < 0)
	{
		ft_print_error(ERR_FORK_FAIL);
		ft_cleanup_pipes(p->pipes, ft_count_pipes(sh->tokens));
		ft_free(p->pipes);
		ft_free(p->pids);
		exit(g_exit_status);
	}
	return (pid);
}

/**
 * @brief Waits for all child processes to finish.
 *
 * @details
 * This function takes an array of process IDs and the number of children
 * and waits for all of them to finish using waitpid(). If a child process
 * exited normally, it sets the global exit status to the exit status of
 * the child process.
 *
 * @param [in] pids An array of process IDs of the child processes to wait for.
 * @param [in] num_children The number of child processes to wait for.
 */
static void	ft_wait_for_children(pid_t *pids, int num_children)
{
	int		i;
	int		status;

	i = 0;
	while (i < num_children)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}
