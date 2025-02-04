/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 16:07:24 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void ft_allocate_tokens(t_shell *shell);
static void ft_process_input(t_shell *shell);

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
	shell->parser->escaped = 0;
	if (ft_process_and_tokenize(shell) == ERROR)
		return (ERROR);
	return (SUCCESS);
	return (SUCCESS);
}

/**
 * @brief Allocates memory for the tokens list based on the parser's token count.
 *
 * If the parser's token count is 0 or negative, the function does nothing.
 *
 * @param shell A pointer to the shell structure whose tokens list is to be
 *              allocated.
 */
static void ft_allocate_tokens(t_shell *shell)
{
	int token_count;

	token_count = shell->parser->token_count;
	if (token_count <= 0)
		return ;
	shell->tokens = ft_safe_malloc(token_count * sizeof(t_token));
}


/**
 * @brief Processes the input string and updates the parser's state.
 *
 * This function iterates through the input string character by character,
 * updating the parser's state based on the current character and the current
 * state. It handles transitions between general, quote, word, and operator
 * states by calling the respective state handling functions. The parser's
 * index is incremented after each character is processed. If the end of the
 * input string is reached while in a quote state, the function returns early
 * without further processing.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and the parser state to be updated.
 */

static void	ft_process_input(t_shell *shell)
{
	const char	*input;
	size_t		i;

	input = shell->input;
	i = 0;
	while (input[i])
	{
		if (shell->parser->state == STATE_GENERAL)
			ft_handle_general_state(shell->parser, input);
		else if (shell->parser->quote_state != NO_QUOTE)
			ft_handle_quote_state(shell->parser, input);
		else if (shell->parser->state == STATE_IN_WORD)
			ft_handle_word_state(shell->parser, input);
		else if (shell->parser->state == STATE_IN_OPERATOR)
			ft_handle_operator_state(shell->parser, input);
		if (input[i] == '\0' && shell->parser->quote_state != NO_QUOTE)
			return ;
		i++;
	}
}
