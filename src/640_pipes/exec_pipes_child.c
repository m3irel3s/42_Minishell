/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/12 17:35:09 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status		ft_handle_redirects(t_shell *shell);
static void			ft_setup_child_redirects(int i, t_pipe *pipes,
						int num_pipes);
static t_token		*ft_copy_tokens(t_token *start, t_token *end);
static t_token		*ft_prepare_child_tokens(t_token *curr_cmd);

/**
 * @brief Executes a command in a child process, with pipes.
 *
 * @details
 * This function takes a shell structure, a token pointer to the current command,
 * an index and a pipes structure as arguments. It first sets up the redirections
 * for the child process, copies the tokens up to the next pipe token and
 * executes the command in a child process. It then cleans up and exits the child
 * process.
 *
 * @param [in] sh The shell structure to execute the command in.
 * @param [in] curr_cmd A pointer to the current command token.
 * @param [in] i The index of the current command.
 * @param [in] pipes The pipes structure.
 */
void	ft_execute_child(t_shell *sh, t_token *curr_cmd, int i,
	t_pipe *pipes)
{
	t_token		*cmd_copy;
	int			num_pipes;
	t_status	redir_status;

	sh->tml->is_terminal = isatty(STDIN_FILENO);
	num_pipes = ft_count_pipes(sh->tokens);
	ft_setup_child_redirects(i, pipes, num_pipes);
	cmd_copy = ft_prepare_child_tokens(curr_cmd);
	if (!cmd_copy)
	{
		ft_print_error(ERR_COPY_TOKENS);
		exit(g_gbl.g_exit_status);
	}
	ft_cleanup_tokens(sh);
	sh->tokens = cmd_copy;
	ft_create_redirection_list(sh);
	redir_status = ft_handle_redirects(sh);
	ft_close_child_pipes(pipes, num_pipes);
	ft_free(pipes);
	if (redir_status == ERROR)
		ft_clean_and_exit(sh);
	if (sh->tokens)
		ft_execute_command(sh, ft_get_cmd_type(sh->tokens->val.value));
	ft_cleanup_w_env(sh);
	ft_free_arr(sh->temp_files);
	exit(g_gbl.g_exit_status);
}

/**
 * @brief Applies all redirections in the shell's redirection list.
 *
 * Iterates through the shell's redirection list and applies each
 * redirection using the appropriate redirection function.
 *
 * @param shell The shell structure containing the redirection list.
 * @return SUCCESS if all redirections are successful, otherwise ERROR.
 */
static t_status	ft_handle_redirects(t_shell *shell)
{
	t_redirect	*redirect;
	t_status	status;

	status = SUCCESS;
	redirect = shell->redirects;
	while (redirect)
	{
		if (ft_apply_redirection(redirect) == ERROR)
			status = ERROR;
		redirect = redirect->next;
	}
	return (status);
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
