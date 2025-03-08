/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 11:15:47 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_setup_child_redirects(int i, t_pipe *pipes, int num_pipes);
static t_token	*ft_copy_tokens(t_token *start, t_token *end);
static t_token	*ft_prepare_child_tokens(t_token *curr_cmd);

void ft_execute_child(t_shell *sh, t_token *curr_cmd, int i, t_pipe *pipes)
{
	t_token *cmd_copy;
	int num_pipes;
	t_redirect *redirect;

	num_pipes = ft_count_pipes(sh->tokens);

	// Step 1: Set up default pipe redirections
	ft_setup_child_redirects(i, pipes, num_pipes);

	// Step 2: Prepare the command's tokens and extract redirections
	cmd_copy = ft_prepare_child_tokens(curr_cmd);
	if (!cmd_copy)
		exit(EXIT_FAILURE);
	ft_cleanup_tokens(sh);
	sh->tokens = cmd_copy;
	ft_create_redirection_list(sh); // Extracts redirections into sh->redirects

	// Step 3: Apply command-specific redirections (overrides pipes if present)
	redirect = sh->redirects;
	while (redirect)
	{
		if (redirect->type == REDIRECT_IN)
		{
			int fd = open(redirect->filename, O_RDONLY);
			if (fd == -1)
			{
				ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
				ft_print_error(ERR_DUP2_FAIL);
			close(fd);
		}
		else if (redirect->type == REDIRECT_OUT)
		{
			int fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
				ft_print_error(ERR_DUP2_FAIL);
			close(fd);
		}
		else if (redirect->type == REDIRECT_APPEND)
		{
			int fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				ft_printf(STDERR_FILENO, ERR_REDIR_NO_FILE, redirect->filename);
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
				ft_print_error(ERR_DUP2_FAIL);
			close(fd);
		}
		redirect = redirect->next;
	}

	// Step 4: Clean up and execute the command
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

static t_token *ft_copy_tokens(t_token *start, t_token *end)
{
	t_token *new_list = NULL;
	t_token *tail = NULL;
	t_token *new_node;

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
		new_node->prev = tail;  // Set prev to the previous node
		if (!new_list)
			new_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		start = start->next;
	}
	return (new_list);
}
