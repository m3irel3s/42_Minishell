/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:43:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 20:04:10 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// cmd1 writes to fd[1] of Pipe 1.
// cmd2 reads from fd[0] of Pipe 1 and writes to fd[3] of Pipe 2.
// cmd3 reads from fd[2] of Pipe 2.

static t_pipe	*ft_allocate_and_create_pipes(t_token *tokens, t_pipe *pipes);
static int		ft_count_pipes(t_token *tokens);
static void		ft_setup_child_redirections(int i, t_pipe *pipes, int num_pipes);
static void		ft_close_child_pipes(t_pipe *pipes, int num_pipes);
static t_token	*ft_copy_tokens(t_token *start, t_token *end);
static void		ft_execute_child(t_shell *shell, t_token *cmd_tokens, int i, t_pipe *pipes, int num_pipes);
static void		ft_advance_to_next_cmd(t_token **curr_cmd);

void	ft_handle_pipes(t_shell *shell)
{
	int		num_pipes = ft_count_pipes(shell->tokens);
	t_pipe	*pipes = ft_allocate_and_create_pipes(shell->tokens, NULL);
	t_token	*curr_cmd = shell->tokens;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < num_pipes + 1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_execute_child(shell, curr_cmd, i, pipes, num_pipes);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		ft_advance_to_next_cmd(&curr_cmd);
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i].read_fd);
		close(pipes[i].write_fd);
		i++;
	}
	i = 0;
	while (i < num_pipes + 1)
	{
		wait(NULL);
		i++;
	}
	free(pipes);
}

static t_pipe	*ft_allocate_and_create_pipes(t_token *tokens, t_pipe *pipes)
{
	int	i;
	int	num_pipes;
	int	pipe_fds[2];

	num_pipes = ft_count_pipes(tokens);
	pipes = ft_safe_malloc(sizeof(t_pipe) * num_pipes);
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fds) == -1)
		{
			ft_printf(2, "minishell: error creating pipe\n");
			return (NULL);
		}
		pipes[i].read_fd = pipe_fds[0];
		pipes[i].write_fd = pipe_fds[1];
		i++;
	}
	return (pipes);
}

static int	ft_count_pipes(t_token *tokens)
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

static void	ft_setup_child_redirections(int i, t_pipe *pipes, int num_pipes)
{
	if (i > 0)
		dup2(pipes[i - 1].read_fd, STDIN_FILENO);
	if (i < num_pipes)
		dup2(pipes[i].write_fd, STDOUT_FILENO);
}

static void	ft_close_child_pipes(t_pipe *pipes, int num_pipes)
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

static t_token	*ft_copy_tokens(t_token *start, t_token *end)
{
	t_token	*new_list = NULL;
	t_token	*tail = NULL;
	t_token	*new_node;

	while (start != end && start)
	{
		new_node = ft_safe_malloc(sizeof(t_token));
		*new_node = *start;
		new_node->next = NULL;
		if (!new_list)
			new_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		start = start->next;
	}
	return (new_list);
}

static void	ft_execute_child(t_shell *shell, t_token *curr_cmd, int i, t_pipe *pipes, int num_pipes)
{
	t_token	*cmd_end;
	t_token	*cmd_copy;

	ft_setup_child_redirections(i, pipes, num_pipes);
	ft_close_child_pipes(pipes, num_pipes);
	cmd_end = curr_cmd;
	while (cmd_end && cmd_end->type != PIPE)
		cmd_end = cmd_end->next;
	cmd_copy = ft_copy_tokens(curr_cmd, cmd_end);
	shell->tokens = cmd_copy;
	ft_execute_command(shell, ft_get_cmd_type(shell->tokens->value));
	exit(EXIT_SUCCESS);
}

static void	ft_advance_to_next_cmd(t_token **curr_cmd)
{
	while (*curr_cmd && (*curr_cmd)->type != PIPE)
		*curr_cmd = (*curr_cmd)->next;
	if (*curr_cmd)
		*curr_cmd = (*curr_cmd)->next;
}
