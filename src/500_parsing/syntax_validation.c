/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 09:43:52 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Validates the syntax of a tokenized input string.
 *
 * Iterates through a linked list of tokens and checks for valid syntax.
 * If an error is found, an appropriate error message is printed to
 * STDERR_FILENO and the function returns ERROR. If all operations succeed,
 * the function returns SUCCESS.
 *
 * Note: The checks for valid syntax are as follows:
 * - A pipe cannot be the first or last token in the input string.
 * - A pipe cannot be followed by another pipe, input redirection,
 *   output redirection, heredoc, or append redirection.
 * - Input redirection, output redirection, heredoc, and append redirection
 *   must be followed by a word.
 * - The last token in the input string must be a word.
 *
 * @param tokens A pointer to the first token in the linked list of tokens.
 *
 * @return Returns SUCCESS if the input is successfully validated;
 *         otherwise, returns ERROR.
 */
t_status	ft_validate_syntax(t_token *tokens) {
	t_token *current;
	t_token_type prev;
	t_token_type type;

	current = tokens;
	prev = -1;
	while (current)
	{
		type = current->type;
		if (type == PIPE && (prev == -1 || prev == PIPE || prev == REDIRECT_IN
			|| prev == REDIRECT_OUT || prev == HEREDOC || prev == REDIRECT_APPEND))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			return (ERROR);
		}
		if ((type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC
			|| type == REDIRECT_APPEND) && (!current->next || current->next->type != WORD))
		{
			ft_putstr_fd("minishell: syntax error near redirect\n", STDERR_FILENO);
			return (ERROR);
		}
		prev = type;
		current = current->next;
	}
	if (prev == PIPE || prev == REDIRECT_IN || prev == REDIRECT_OUT
		|| prev == HEREDOC || prev == REDIRECT_APPEND)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}
