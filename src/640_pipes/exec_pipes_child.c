/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 14:05:35 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_setup_child_redirects(int i, t_pipe *pipes, int num_pipes);
static t_token	*ft_copy_tokens(t_token *start, t_token *end);
static t_token	*ft_prepare_child_tokens(t_token *curr_cmd);

void	ft_execute_child(t_shell *sh, t_token *curr_cmd, int i, t_pipe *pipes)
{
	t_token		*cmd_copy;
	int			num_pipes;
	t_redirect	*redirect;

	num_pipes = ft_count_pipes(sh->tokens);
	ft_setup_child_redirects(i, pipes, num_pipes);
	cmd_copy = ft_prepare_child_tokens(curr_cmd);
	if (!cmd_copy)
		exit(EXIT_FAILURE);
	ft_cleanup_tokens(sh);
	sh->tokens = cmd_copy;
	ft_create_redirection_list(sh);
	redirect = sh->redirects;
	while (redirect)
	{
		ft_apply_redirection(sh, redirect);
		redirect = redirect->next;
	}
	ft_close_child_pipes(pipes, num_pipes);
	ft_free(pipes);
	ft_execute_command(sh, ft_get_cmd_type(sh->tokens->val.value));
	ft_cleanup_w_env(sh);
	exit(g_exit_status);
}

static void	ft_setup_child_redirects(int i, t_pipe *pipes, int num_pipes)
{
	if (i > 0)
		if (dup2(pipes[i - 1].read_fd, STDIN_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
	if (i < num_pipes)
		if (dup2(pipes[i].write_fd, STDOUT_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
}

static t_token	*ft_prepare_child_tokens(t_token *curr_cmd)
{
	t_token	*cmd_end;
	t_token	*cmd_copy;

	cmd_end = curr_cmd;
	while (cmd_end && cmd_end->type != PIPE)
		cmd_end = cmd_end->next;
	cmd_copy = ft_copy_tokens(curr_cmd, cmd_end);
	return (cmd_copy);
}

static t_token	*ft_copy_tokens(t_token *start, t_token *end)
{
	t_token	*new_list;
	t_token	*tail;
	t_token	*new_node;

	new_list = NULL;
	tail = NULL;
	while (start != end && start)
	{
		new_node = ft_safe_calloc(sizeof(t_token));
		if (!new_node)
			return (NULL);
		new_node->val.og_value = ft_safe_strdup(start->val.og_value);
		new_node->val.value = ft_safe_strdup(start->val.value);
		new_node->type = start->type;
		new_node->quoted = start->quoted;
		new_node->next = NULL;
		new_node->prev = tail;
		if (!new_list)
			new_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		start = start->next;
	}
	return (new_list);
}
