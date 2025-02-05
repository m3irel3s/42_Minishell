/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:13:19 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/05 15:35:21 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Handles the general state in the parser.
 *
 * Checks the current character for various conditions and transitions the parser
 * to the appropriate state. If the character is an operator, it transitions to
 * the operator state. If the character is a quote, it sets the quote state
 * accordingly and transitions to the word state. If the character is a word
 * character, it transitions to the word state. It also handles escaped
 * characters.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and the parser state to be updated.
 */
void	ft_handle_general_state(t_shell *shell)
{
	printf("Handling general state...\n");
	if (ft_is_operator(shell->input[shell->parser->index]) && !shell->parser->escaped && shell->parser->quote_state == NO_QUOTE)
	{
		printf("Found operator, transitioning to operator state...\n");
		shell->parser->state = STATE_IN_OPERATOR;
		shell->parser->token_count++;
		if (shell->parser->token_count == 1)
			shell->parser->start = shell->parser->index;
	}
	else if (shell->input[shell->parser->index] == '\'' && !shell->parser->escaped)
	{
		printf("Found single quote, setting quote state...\n");
		shell->parser->quote_state = SINGLE_QUOTE;
		shell->parser->state = STATE_IN_WORD;
		shell->parser->token_count++;
		if (shell->parser->token_count == 1)
			shell->parser->start = shell->parser->index;
	}
	else if (shell->input[shell->parser->index] == '"' && !shell->parser->escaped)
	{
		printf("Found double quote, setting quote state...\n");
		shell->parser->quote_state = DOUBLE_QUOTE;
		shell->parser->state = STATE_IN_WORD;
		shell->parser->token_count++;
		if (shell->parser->token_count == 1)
			shell->parser->start = shell->parser->index;
	}
	else if (!ft_is_space(shell->input[shell->parser->index]))
	{
		printf("Found word character, transitioning to word state...\n");
		shell->parser->token_count++;
		if (shell->parser->token_count == 1)
			shell->parser->start = shell->parser->index;
		shell->parser->state = STATE_IN_WORD;
	}
	shell->parser->escaped = (shell->input[shell->parser->index] == '\\' && !shell->parser->escaped);
	printf("Escaped flag set to %d\n", shell->parser->escaped);
}

/**
 * @brief Handles the quote state in the parser.
 *
 * This function checks if the current character is a closing single or double
 * quote, and if so, resets the quote state to NO_QUOTE and transitions the
 * parser to the general state. It also handles the case where the current
 * character is a backslash in double quotes, and sets the escaped flag.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and the parser state to be updated.
 */
void	ft_handle_quote_state(t_shell *shell)
{
	printf("Handling quote state...\n");
	if (shell->parser->quote_state == SINGLE_QUOTE && shell->input[shell->parser->index] == '\'' && !shell->parser->escaped)
	{
		printf("Found closing single quote, resetting quote state...\n");
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
			return;
		shell->parser->quote_state = NO_QUOTE;
		shell->parser->state = STATE_GENERAL;
	}
	else if (shell->parser->quote_state == DOUBLE_QUOTE && shell->input[shell->parser->index] == '"' && !shell->parser->escaped)
	{
		printf("Found closing double quote, resetting quote state...\n");
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
			return;
		shell->parser->quote_state = NO_QUOTE;
		shell->parser->state = STATE_GENERAL;
	}
	else if (shell->parser->quote_state == DOUBLE_QUOTE && shell->input[shell->parser->index] == '\\'
		&& !shell->parser->escaped)
	{
		printf("Found backslash in double quotes, setting escaped flag...\n");
		shell->parser->escaped = 1;
		return ;
	}
	if (shell->parser->escaped)
	{
		printf("Resetting escaped flag...\n");
		shell->parser->escaped = 0;
		return ;
	}
}

/**
 * @brief Handles the word state in the parser.
 *
 * This function checks if the current character is a space or an operator
 * outside of quotes, and if so, transitions the parser to the general state.
 * Additionally, it handles the case where the current character is a closing
 * quote, and resets the quote state.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and the parser state to be updated.
 */
void	ft_handle_word_state(t_shell *shell)
{
	printf("Handling word state...\n");
	if (shell->parser->quote_state == NO_QUOTE && ft_is_space(shell->input[shell->parser->index]))
	{
		printf("Found space outside quotes, transitioning to general state...\n");
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index) == ERROR)
			return ;
		shell->parser->state = STATE_GENERAL;
		shell->parser->start = shell->parser->index + 1;
	}
	else if (shell->parser->quote_state == NO_QUOTE && ft_is_operator(shell->input[shell->parser->index]))
	{
		printf("Found operator outside quotes, transitioning to general state...\n");
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index) == ERROR)
			return ;
		shell->parser->state = STATE_GENERAL;
		shell->parser->index--;
	}
	else if (shell->parser->quote_state == SINGLE_QUOTE && shell->input[shell->parser->index] == '\'' && !shell->parser->escaped)
	{
		printf("Found closing single quote, resetting quote state...\n");
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
			return ;
		shell->parser->quote_state = NO_QUOTE;
		shell->parser->state = STATE_GENERAL;
	}
	else if (shell->parser->quote_state == DOUBLE_QUOTE && shell->input[shell->parser->index] == '"' && !shell->parser->escaped)
	{
		printf("Found closing double quote, resetting quote state...\n");
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
			return ;
		shell->parser->quote_state = NO_QUOTE;
		shell->parser->state = STATE_GENERAL;
	}
	if (shell->parser->quote_state != NO_QUOTE && ft_is_space(shell->input[shell->parser->index]))
	{
		shell->parser->state = STATE_IN_WORD;
	}
	shell->parser->escaped = (shell->input[shell->parser->index] == '\\' && !shell->parser->escaped);
	printf("Escaped flag set to %d\n", shell->parser->escaped);
}

/**
 * @brief Handles the operator state in the parser.
 *
 * Checks if the current character is part of an operator sequence
 * or if it is a standalone operator. If it is an operator sequence,
 * it sets the parser's state to STATE_IN_OPERATOR; otherwise, it
 * sets the parser's state to STATE_GENERAL and attempts to create
 * and add a token to the shell's tokens list.
 *
 * @param shell A pointer to the shell structure containing the input
 *              string and the parser state to be updated.
 */
void	ft_handle_operator_state(t_shell *shell)
{
	if (shell->parser->index > 0 && shell->input[shell->parser->index] == shell->input[shell->parser->index - 1] && !shell->parser->escaped)
	{
		if (shell->input[shell->parser->index] == '<' || shell->input[shell->parser->index] == '>')
		{
			shell->parser->state = STATE_IN_OPERATOR;
			return;
		}
	}
	else
	{
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index) == ERROR)
			return;
		shell->parser->state = STATE_GENERAL;
		shell->parser->index--;
	}
}
