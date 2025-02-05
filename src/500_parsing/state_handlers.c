/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:13:19 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/05 13:52:55 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/**
 * @brief Handles the general state of the parser.
 *
 * When the parser is in the general state, this function checks if the current
 * character is an operator, a single quote, a double quote, or a word character.
 * If it is an operator, the parser transitions to the operator state and the
 * token count is incremented. If it is a single quote or a double quote, the
 * parser transitions to the word state and the quote state is set accordingly.
 * If it is a word character, the parser transitions to the word state and the
 * token count is incremented. The escaped flag is set if the current character
 * is a backslash and it is not escaped.
 *
 * @param p A pointer to the parser structure.
 * @param input The input string to be parsed.
 */
void	ft_handle_general_state(t_parser *p, const char *input)
{
	printf("Handling general state...\n");
	if (ft_is_operator(input[p->index]) && !p->escaped && p->quote_state == NO_QUOTE)
	{
		printf("Found operator, transitioning to operator state...\n");
		p->state = STATE_IN_OPERATOR;
		p->token_count++;
	}
	else if (input[p->index] == '\'' && !p->escaped)
	{
		printf("Found single quote, setting quote state...\n");
		p->quote_state = SINGLE_QUOTE;
		p->state = STATE_IN_WORD;
		p->token_count++;
	}
	else if (input[p->index] == '"' && !p->escaped)
	{
		printf("Found double quote, setting quote state...\n");
		p->quote_state = DOUBLE_QUOTE;
		p->state = STATE_IN_WORD;
		p->token_count++;
	}
	else if (!ft_is_space(input[p->index]))
	{
		printf("Found word character, transitioning to word state...\n");
		p->token_count++;
		p->state = STATE_IN_WORD;
	}
	p->escaped = (input[p->index] == '\\' && !p->escaped);
	printf("Escaped flag set to %d\n", p->escaped);
}

/**
 * @brief Handles the quote state of the parser.
 *
 * When the parser is in a quote state, this function checks if the current
 * character is a closing quote or a backslash. If it is a closing quote, the
 * parser transitions back to the general state. If it is a backslash, the
 * escaped flag is set.
 *
 * @param p A pointer to the parser structure.
 * @param input The input string to be parsed.
 */
void	ft_handle_quote_state(t_parser *p, const char *input)
{
	printf("Handling quote state...\n");
	if (p->quote_state == SINGLE_QUOTE && input[p->index] == '\''
		&& !p->escaped)
	{
		printf("Found closing single quote, resetting quote state...\n");
		p->quote_state = NO_QUOTE;
		p->state = STATE_GENERAL;
	}
	else if (p->quote_state == DOUBLE_QUOTE && input[p->index] == '"'
		&& !p->escaped)
	{
		printf("Found closing double quote, resetting quote state...\n");
		p->quote_state = NO_QUOTE;
		p->state = STATE_GENERAL;
	}
	else if (p->quote_state == DOUBLE_QUOTE && input[p->index] == '\\'
		&& !p->escaped)
	{
		printf("Found backslash in double quotes, setting escaped flag...\n");
		p->escaped = 1;
		return ;
	}
	if (p->escaped)
	{
		printf("Resetting escaped flag...\n");
		p->escaped = 0;
		return ;
	}
}

/**
 * @brief Handles the word state of the parser.
 *
 * In the word state, the parser checks if the current character is a whitespace
 * or an operator. If it is, the parser transitions back to the general state.
 * If it is not, the parser stays in the word state.
 *
 * @param p A pointer to the parser structure.
 * @param input The input string to be parsed.
 */
void	ft_handle_word_state(t_parser *p, const char *input)
{
	printf("Handling word state...\n");
	if (p->quote_state == NO_QUOTE && (ft_is_space(input[p->index]) || ft_is_operator(input[p->index])))
	{
		printf("Found space or operator outside quotes, transitioning to general state...\n");
		p->state = STATE_GENERAL;
		p->index--;
	}
	else if (p->quote_state == SINGLE_QUOTE && input[p->index] == '\'' && !p->escaped)
	{
		printf("Found closing single quote, resetting quote state...\n");
		p->quote_state = NO_QUOTE;
		p->state = STATE_GENERAL;
	}
	else if (p->quote_state == DOUBLE_QUOTE && input[p->index] == '"' && !p->escaped)
	{
		printf("Found closing double quote, resetting quote state...\n");
		p->quote_state = NO_QUOTE;
		p->state = STATE_GENERAL;
	}
	if (p->quote_state != NO_QUOTE && ft_is_space(input[p->index]))
	{
		p->state = STATE_IN_WORD;
	}
	p->escaped = (input[p->index] == '\\' && !p->escaped);
	printf("Escaped flag set to %d\n", p->escaped);
}

/**
 * @brief Handles the operator state of the parser.
 *
 * In the operator state, the parser checks if the current character is the same
 * as the previous one and if it is not escaped. If it is, the parser transitions
 * back to the operator state. If it is not, the parser checks if the current
 * character is a whitespace or an operator. If it is, the parser transitions
 * back to the general state. If it is not, the parser stays in the operator
 * state.
 *
 * @param p A pointer to the parser structure.
 * @param input The input string to be parsed.
 */
void	ft_handle_operator_state(t_parser *p, const char *input)
{
	if (p->index > 0 && input[p->index] == input[p->index - 1] && !p->escaped)
	{
		if ((input[p->index] == '<' || input[p->index] == '>') &&
			input[p->index - 1] == input[p->index - 2])
		{
			ft_putstr_fd("Error: Invalid operator sequence.\n", STDERR_FILENO);
			p->state = STATE_ERROR;
			return ;
		}
		p->state = STATE_IN_OPERATOR;
	}
	else if (!ft_is_operator(input[p->index]) || ft_is_space(input[p->index]))
	{
		p->state = STATE_GENERAL;
		p->index--;
	}
}
