/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:00:00 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/26 15:20:27 by meferraz         ###   ########.fr       */
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
/**
 * @brief Executes a command in a child process in a pipeline.
 *
 * This function sets up redirections for the child process, closes the
 * necessary pipes, and executes the command. After execution is complete,
 * it frees the tokens and exits the child process with the exit status
 * of the command.
 *
 * @param shell The shell object
 * @param curr_cmd The current command token
 * @param i The index of the current command in the pipeline
 * @param pipes The array of pipes for the pipeline
 * @param num_pipes The number of pipes in the pipeline
 */
void	ft_execute_child(t_shell *shell, t_token *curr_cmd, int i, t_pipe *pipes, int num_pipes)
{
	t_token	*cmd_end;
	t_token	*cmd_copy;

	ft_setup_child_redirections(i, pipes, num_pipes);
	ft_close_child_pipes(pipes, num_pipes);
	cmd_end = curr_cmd;
	while (cmd_end && cmd_end->type != PIPE)
		cmd_end = cmd_end->next;
	cmd_copy = ft_copy_tokens(curr_cmd, cmd_end);
	if (!cmd_copy)
		exit(EXIT_FAILURE);
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
	shell->tokens = cmd_copy;
	ft_free_redirects(shell->redirects);
	shell->redirects = NULL;
	ft_create_redirection_list(shell);
	ft_handle_redirections(shell);
	ft_execute_command(shell, ft_get_cmd_type(shell->tokens->val.value));
	ft_free_token(cmd_copy);
	exit(g_exit_status);
}

/**
 * @brief Sets up redirections for a child process in a pipe chain.
 *
 * This function duplicates the read file descriptor of the previous pipe
 * (if this is not the first command in the chain) and the write file descriptor
 * of the current pipe (if this is not the last command in the chain) to
 * the standard input and output, respectively.
 *
 * @param i The position of the current command in the pipe chain.
 * @param pipes The array of pipes containing read and write file descriptors.
 * @param num_pipes The number of pipes in the pipe chain.
 */
void	ft_setup_child_redirections(int i, t_pipe *pipes, int num_pipes)
{
	if (i > 0)
		if (dup2(pipes[i - 1].read_fd, STDIN_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
	if (i < num_pipes)
		if (dup2(pipes[i].write_fd, STDOUT_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
}

/**
 * @brief Closes all pipe file descriptors for a child process.
 *
 * This function iterates through the array of pipe structures, closing
 * both the read and write file descriptors for each pipe. It is used
 * in child processes to properly close unused pipe ends after setting
 * up redirections.
 *
 * @param pipes An array of pipe structures containing file descriptors.
 * @param num_pipes The number of pipes in the array.
 */

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

/**
 * Creates a deep copy of the linked list of tokens from @a start to @a end.
 *
 * @param start The first token to copy.
 * @param end The last token to copy (exclusive).
 *
 * @return A pointer to the first token of the copied list, or NULL if memory
 * allocation fails.
 */
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
