/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 14:43:25 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_handle_redirects(t_shell *shell);
static void		ft_setup_child_redirects(int i, t_pipe *pipes, int num_pipes);
static t_token	*ft_copy_tokens(t_token *start, t_token *end);
static t_token	*ft_prepare_child_tokens(t_token *curr_cmd);

/**
 * @brief Executes a command within a child process in a pipeline.
 *
 * @details
 * This function sets up necessary redirections for the child process,
 * prepares a copy of the command tokens, applies any defined redirections,
 * and executes the command. It also closes and frees resources related to pipes
 * and cleans up the shell's environment before exiting the child process.
 *
 * @param [in] sh The shell structure containing the current shell state.
 * @param [in] curr_cmd The current command token to be executed.
 * @param [in] i The index of the current command in the pipeline.
 * @param [in] pipes The pipes structure containing file descriptors for
 * communication.
 */
void	ft_execute_child(t_shell *sh, t_token *curr_cmd, int i,
		t_pipe *pipes)
{
	t_token		*cmd_copy;
	int			num_pipes;

	num_pipes = ft_count_pipes(sh->tokens);
	ft_setup_child_redirects(i, pipes, num_pipes);
	cmd_copy = ft_prepare_child_tokens(curr_cmd);
	if (!cmd_copy)
	{
		ft_print_error(ERR_COPY_TOKENS);
		exit(g_exit_status);
	}
	ft_cleanup_tokens(sh);
	sh->tokens = cmd_copy;
	ft_create_redirection_list(sh);
	ft_handle_redirects(sh);
	ft_close_child_pipes(pipes, num_pipes);
	ft_free(pipes);
	ft_execute_command(sh, ft_get_cmd_type(sh->tokens->val.value));
	ft_cleanup_w_env(sh);
	exit(g_exit_status);
}

/**
 * @brief Applies all redirections for the current shell command.
 *
 * Iterates through the shell's redirection list and applies each
 * redirection using the appropriate redirection function.
 *
 * @param shell A pointer to the shell structure containing the
 *              redirection list.
 */
static void	ft_handle_redirects(t_shell *shell)
{
	t_redirect	*redirect;

	redirect = shell->redirects;
	while (redirect)
	{
		ft_apply_redirection(shell, redirect);
		redirect = redirect->next;
	}
}

/**
 * @brief Sets up redirections for the current child process in a pipeline.
 *
 * @details
 * This function takes the index of the current command in the pipeline,
 * the pipes structure containing file descriptors for communication,
 * and the number of pipes in the pipeline. It sets up the necessary
 * redirections for the child process by duplicating the read and write
 * file descriptors of the pipes into the standard input and output
 * file descriptors of the child process. If a failure occurs during
 * the duplication, an error message is printed.
 *
 * @param [in] i The index of the current command in the pipeline.
 * @param [in] pipes The pipes structure containing file descriptors for
 * communication.
 * @param [in] num_pipes The number of pipes in the pipeline.
 */
static void	ft_setup_child_redirects(int i, t_pipe *pipes, int num_pipes)
{
	if (i > 0)
		if (dup2(pipes[i - 1].read_fd, STDIN_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
	if (i < num_pipes)
		if (dup2(pipes[i].write_fd, STDOUT_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
}

/**
 * @brief Creates a copy of the tokens of the current command for the child
 * process.
 *
 * @details
 * This function takes a pointer to the current command token and copies all
 * the tokens up to the next pipe token. The copied tokens are returned as a
 * linked list.
 *
 * @param [in] curr_cmd A pointer to the current command token.
 * @return A pointer to the head of the copied token linked list.
 */
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

/**
 * @brief Creates a copy of a range of tokens in a linked list.
 *
 * @details
 * This function takes two pointers to tokens, @p start and @p end, and
 * creates a new linked list containing all the tokens from @p start up
 * to but not including @p end. The new linked list is then returned.
 *
 * @param [in] start A pointer to the first token of the range.
 * @param [in] end A pointer to the token after the last token of the range.
 * @return A pointer to the head of the new linked list or NULL if
 * allocation fails.
 */
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
