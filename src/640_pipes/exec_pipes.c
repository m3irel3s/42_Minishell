/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:43:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/05 16:50:18 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_wait_for_children(int num_children);
static void	ft_fork_exec(t_shell *sh, t_token *curr_cmd, t_pipe *pipes, int i);

void	ft_handle_pipes(t_shell *shell)
{
	t_pipe	*pipes;
	t_token	*curr_cmd;
	int		i;

	pipes = ft_allocate_and_create_pipes(shell->tokens);
	if (!pipes)
		ft_print_error(ERR_PIPE_FAIL);
	if (!pipes)
		return ;
	curr_cmd = shell->tokens;
	i = 0;
	while (i < ft_count_pipes(shell->tokens) + 1)
	{
		ft_fork_exec(shell, curr_cmd, pipes, i);
		ft_advance_to_next_cmd(&curr_cmd);
		i++;
	}
	ft_cleanup_pipes(pipes, ft_count_pipes(shell->tokens));
	ft_wait_for_children(ft_count_pipes(shell->tokens) + 1);
	ft_free(pipes);
}

static void	ft_fork_exec(t_shell *sh, t_token *curr_cmd, t_pipe *pipes, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_execute_child(sh, curr_cmd, i, pipes);
		exit(g_exit_status);
	}
	else if (pid < 0)
	{
		ft_print_error(ERR_FORK_FAIL);
		ft_cleanup_pipes(pipes, ft_count_pipes(sh->tokens));
		ft_free(pipes);
		exit(EXIT_FAILURE);
	}
}

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
