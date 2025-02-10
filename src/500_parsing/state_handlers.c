/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:13:19 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 09:33:36 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_general_state(t_shell *shell);
static void	ft_handle_quote_state(t_shell *shell);
static void	ft_handle_word_state(t_shell *shell);
static void	ft_handle_operator_state(t_shell *shell);

/**
 * @brief Handles the current state of the parser based on the current character.
 *
 * Checks the current state of the parser and calls the appropriate handler
 * function based on the current character. If the state has changed from
 * STATE_IN_WORD or STATE_IN_OPERATOR to STATE_GENERAL, creates a token with
 * the last read string and adds it to the list of tokens.
 *
 * @param shell The t_shell structure containing the parser.
 */
void	ft_handle_current_state(t_shell *shell)
{
	t_parser_state prev_state;

	prev_state = shell->parser->state;
	if (shell->parser->state == STATE_GENERAL)
		ft_handle_general_state(shell);
	else if (shell->parser->quote_state != NO_QUOTE)
		ft_handle_quote_state(shell);
	else if (shell->parser->state == STATE_IN_WORD)
		ft_handle_word_state(shell);
	else if (shell->parser->state == STATE_IN_OPERATOR)
		ft_handle_operator_state(shell);
	if ((prev_state == STATE_IN_WORD && shell->parser->state == STATE_GENERAL) ||
		(prev_state == STATE_IN_OPERATOR && shell->parser->state == STATE_GENERAL))
	{
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index) == ERROR)
			shell->parser->state = STATE_ERROR;
		shell->parser->start = shell->parser->index;
	}
}

/**
 * @brief Handles the general parsing state for the input string.
 *
 * This function checks the current character in the input string and transitions
 * the parser to the appropriate state. It identifies if the character is an
 * operator, a quote, or part of a word and updates the parser's state and
 * starting index accordingly. It also manages the escape character logic.
 *
 * @param shell A pointer to the shell structure containing the input string and
 *              parser state information.
 */

static void	ft_handle_general_state(t_shell *shell)
{
	char current_char;

	current_char = shell->input[shell->parser->index];
	if (ft_is_operator(current_char) && !shell->parser->escaped)
	{
		shell->parser->state = STATE_IN_OPERATOR;
		shell->parser->start = shell->parser->index;
	}
	else if ((current_char == '\'' || current_char == '"') && !shell->parser->escaped)
	{
		if (current_char == '\'')
			shell->parser->quote_state = SINGLE_QUOTE;
		else
			shell->parser->quote_state = DOUBLE_QUOTE;
		shell->parser->state = STATE_IN_WORD;
		shell->parser->start = shell->parser->index;
	}
	else if (!ft_is_space(current_char))
	{
		shell->parser->state = STATE_IN_WORD;
		shell->parser->start = shell->parser->index;
	}
	shell->parser->escaped = (current_char == '\\' && !shell->parser->escaped);
}

/**
 * @brief Handles the quote state for the input string.
 *
 * Checks if the current character is a single or double quote and
 * transitions the parser to the appropriate state. If the current
 * character is a closing quote, it resets the quote state and
 * creates a token. If the current character is an escaped character,
 * it sets the escaped flag. If the current character is not a quote
 * or escaped character, it resets the escaped flag.
 *
 * @param shell A pointer to the shell structure containing the input
 *              string and parser state information.
 */
static void	ft_handle_quote_state(t_shell *shell)
{
	char current_char;

	current_char = shell->input[shell->parser->index];
	if ((shell->parser->quote_state == SINGLE_QUOTE && current_char == '\'') ||
		(shell->parser->quote_state == DOUBLE_QUOTE && current_char == '"'))
	{
		if (!shell->parser->escaped)
		{
			if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
				shell->parser->state = STATE_ERROR;
			shell->parser->quote_state = NO_QUOTE;
			shell->parser->state = STATE_GENERAL;
		}
	}
	else if (shell->parser->quote_state == DOUBLE_QUOTE && current_char == '\\' && !shell->parser->escaped)
	{
		shell->parser->escaped = 1;
		return;
	}
	shell->parser->escaped = 0;
}

/**
 * @brief Handles the word state for the input string.
 *
 * Checks if the current character is a word character or not. If it is not a word
 * character, it transitions the parser to the general state and creates a token
 * with the previously read string. It also manages the escape character logic.
 *
 * @param shell A pointer to the shell structure containing the input string and
 *              parser state information.
 */
static void	ft_handle_word_state(t_shell *shell)
{
	char current_char;

	current_char = shell->input[shell->parser->index];
	if (shell->parser->quote_state == NO_QUOTE && (ft_is_space(current_char) || ft_is_operator(current_char)))
	{
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index) == ERROR)
			shell->parser->state = STATE_ERROR;
		shell->parser->state = STATE_GENERAL;
		shell->parser->start = shell->parser->index;
	}
	shell->parser->escaped = (current_char == '\\' && !shell->parser->escaped);
}

/**
 * @brief Handles the operator state for the input string in the parser.
 *
 * This function checks if the current character and the next character in the input
 * form a double operator (like '>>' or '<<'). If so, it advances the parser index
 * and creates a token for the operator, transitioning the parser state back to
 * STATE_GENERAL. If the character is a single operator ('|', '>', '<'), it creates
 * a token and transitions the parser state back to STATE_GENERAL. If the character
 * is not recognized as an operator, it transitions the parser state to STATE_IN_WORD.
 *
 * @param shell A pointer to the shell structure containing the input string and
 *              parser state information.
 */
static void	ft_handle_operator_state(t_shell *shell)
{
	char current_char;
	char next_char;

	current_char = shell->input[shell->parser->index];
	next_char = shell->input[shell->parser->index + 1];
	if ((current_char == '>' && next_char == '>') || (current_char == '<' && next_char == '<'))
	{
		shell->parser->index++;
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
			shell->parser->state = STATE_ERROR;
		shell->parser->state = STATE_GENERAL;
	}
	else if (current_char == '|' || current_char == '>' || current_char == '<')
	{
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index + 1) == ERROR)
			shell->parser->state = STATE_ERROR;
		shell->parser->state = STATE_GENERAL;
	}
	else
		shell->parser->state = STATE_IN_WORD;
}
