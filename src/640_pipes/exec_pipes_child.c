/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/01 15:03:40 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void ft_execute_child(t_shell *shell, t_token *curr_cmd, int i, t_pipe *pipes, int num_pipes)
{
	t_token *cmd_end;
	t_token *cmd_copy;

	ft_setup_child_redirections(i, pipes, num_pipes);
	ft_close_child_pipes(pipes, num_pipes);
	cmd_end = curr_cmd;
	while (cmd_end && cmd_end->type != PIPE)
		cmd_end = cmd_end->next;
	cmd_copy = ft_copy_tokens(curr_cmd, cmd_end);
	if (!cmd_copy)
		exit(EXIT_FAILURE);
	shell->tokens = cmd_copy;
	ft_create_redirection_list(shell);
	ft_handle_redirections(shell);
	if (shell->redirected_stdin != -1)
	{
		dup2(shell->redirected_stdin, STDIN_FILENO);
		close(shell->redirected_stdin);
	}
	if (shell->redirected_stdout != -1)
	{
		dup2(shell->redirected_stdout, STDOUT_FILENO);
		close(shell->redirected_stdout);
	}
	ft_execute_command(shell, ft_get_cmd_type(shell->tokens->val.value));
	ft_free_token(cmd_copy);
	ft_free_redirects(shell->redirects);
	shell->redirects = NULL;
	exit(g_exit_status);
}

void	ft_setup_child_redirections(int i, t_pipe *pipes, int num_pipes)
{
	if (i > 0)
		if (dup2(pipes[i - 1].read_fd, STDIN_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
	if (i < num_pipes)
		if (dup2(pipes[i].write_fd, STDOUT_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
}


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

t_token	*ft_copy_tokens(t_token *start, t_token *end)
{
	t_token	*new_list;
	t_token	*tail;
	t_token	*new_node;

	new_list = NULL;
	tail = NULL;
	while (start != end && start)
	{
		new_node = ft_safe_malloc(sizeof(t_token));
		if (!new_node)
			return (NULL);
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
