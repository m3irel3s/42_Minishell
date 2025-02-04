/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 12:34:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Tokenizes the input string and populates the shell structure's tokens list.
 *
 * This function first processes the input string by adding escaped characters to
 * the parser's index. Then, if the parser is not in a quote state, it allocates
 * memory for the tokens list and populates it with tokens created from the input
 * string.
 *
 * @param shell A pointer to the shell structure whose input string is to be
 *              tokenized.
 *
 * @return SUCCESS if the tokenization succeeds, ERROR otherwise.
 */
int	ft_tokenize(t_shell *shell)
{
	if (!shell || !shell->input)
		return (ERROR);
	ft_process_input(shell);
	if (shell->parser->quote_state != NO_QUOTE)
		return (SUCCESS);
	ft_allocate_tokens(shell);
	shell->parser->index = 0;
	shell->parser->token_count = 0;
	shell->parser->state = STATE_GENERAL;
	shell->parser->quote_state = NO_QUOTE;
	ft_process_and_tokenize(shell);
	return (SUCCESS);
}

static void ft_allocate_tokens(t_shell *shell)
|{
	int token_count;

	token_count = shell->parser->token_count;
	if (token_count <= 0)
		return ;
	shell->tokens = ft_safe_malloc(token_count * sizeof(t_token));
}
