/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:43:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/01 15:03:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_wait_for_children(int num_children);

void ft_handle_pipes(t_shell *shell)
{
	t_pipe	*pipes;
	t_token	*curr_cmd;
	pid_t	pid;
	int		num_pipes;
	int		i;

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
