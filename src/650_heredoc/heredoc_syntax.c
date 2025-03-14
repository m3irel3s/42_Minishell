/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 22:05:41 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Checks the syntax of a heredoc operator.
 *
 * Checks if the next token is a word or a quoted token. If it is not, it prints
 * a syntax error message and sets the exit status to EXIT_FAILURE.
 *
 * @param current The token containing the heredoc operator.
 * @return ERROR if the syntax is invalid, SUCCESS otherwise.
 */
t_status	ft_check_heredoc_syntax(t_token *current)
{
	if (!current->next || (current->next->type != WORD
			&& !current->next->quoted))
		return (ft_print_syntax_error("newline"), ERROR);
	return (SUCCESS);
}

/**
 * @brief Process all heredoc redirections in the shell's token list.
 *
 * Saves the current standard input, processes each heredoc redirection in the
 * shell's token list by calling ft_handle_single_heredoc, and restores the
 * original standard input after all heredocs have been processed.
 *
 * @param shell The shell structure containing the token list.
 * @return SUCCESS if all heredoc redirections were processed
 * successfully, ERROR otherwise.
 */
t_status	ft_process_heredocs(t_shell *shell)
{
	t_token	*current;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (ERROR);
	current = shell->tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (ft_handle_single_heredoc(shell, current) == ERROR)
			{
				if (dup2(saved_stdin, STDIN_FILENO) == -1)
					ft_print_error(ERR_DUP2_FAIL);
				close(saved_stdin);
				return (ERROR);
			}
		}
		current = current->next;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		ft_print_error(ERR_DUP2_FAIL);
	close(saved_stdin);
	return (SUCCESS);
}
