/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void ft_process_input(t_shell *shell);
static t_status ft_process_and_tokenize(t_shell *shell);

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
	{
		ft_putstr_fd("Error: Unmatched quotes.\n", STDERR_FILENO);
		return (ERROR);
	}
	shell->parser->index = 0;
	shell->parser->token_count = 0;
	shell->parser->state = STATE_GENERAL;
	shell->parser->quote_state = NO_QUOTE;
	shell->parser->escaped = 0;
	if (ft_process_and_tokenize(shell) == ERROR)
		return (ERROR);
	return (SUCCESS);
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

	input = shell->input;
	while (input[shell->parser->index])
	{
		if (shell->parser->state == STATE_GENERAL)
			ft_handle_general_state(shell->parser, input);
		else if (shell->parser->quote_state != NO_QUOTE)
			ft_handle_quote_state(shell->parser, input);
		else if (shell->parser->state == STATE_IN_WORD)
			ft_handle_word_state(shell->parser, input);
		else if (shell->parser->state == STATE_IN_OPERATOR)
			ft_handle_operator_state(shell->parser, input);
		shell->parser->index++;
	}
}

/**
 * @brief Tokenizes the input string from the shell.
 *
 * This function processes the input string character by character, updating
 * the parser's state and tokenizing the input based on whitespace and
 * operators. It handles transitions between general, word, and operator
 * states, creating tokens for each identified segment. If the end of the
 * input is reached while still in a word or operator state, the remaining
 * segment is also tokenized. The tokens are added to the shell's token list.
 * The function returns SUCCESS if tokenization completes successfully,
 * otherwise it returns ERROR in case of a failure to create a token.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and parser state.
 * @return Returns SUCCESS if tokenization is successful; otherwise, returns
 *         ERROR.
 */

static t_status ft_process_and_tokenize(t_shell *shell)
{
	const char	*input;
	size_t		start;
	t_token		*token;
	char		*temp;

	input = shell->input;
	start = 0;
	while (input[shell->parser->index])
	{
		if (shell->parser->state == STATE_GENERAL && !ft_is_space(input[shell->parser->index]))
		{
			start = shell->parser->index;
			if (ft_is_operator(input[start]))
				shell->parser->state = STATE_IN_OPERATOR;
			else
				shell->parser->state = STATE_IN_WORD;
		}
		else if ((shell->parser->state == STATE_IN_WORD && ft_is_space(input[shell->parser->index])) ||
				 (shell->parser->state == STATE_IN_OPERATOR && !ft_is_operator(input[shell->parser->index])))
		{
			temp = ft_substr(input, start, shell->parser->index - start);
			if (!temp)
				return (ERROR);
			token = ft_create_token(temp, ft_determine_token_type(temp));
			free(temp);
			if (!token)
				return (ERROR);
			ft_add_token_to_list(shell, token);
			shell->parser->state = STATE_GENERAL;
			start = shell->parser->index + 1;
		}
		shell->parser->index++;
	}
	if (shell->parser->state != STATE_GENERAL && shell->parser->index > start)
	{
		temp = ft_substr(input, start, shell->parser->index - start);
		if (!temp)
			return (ERROR);
		token = ft_create_token(temp, ft_determine_token_type(temp));
		free(temp);
		if (!token)
			return (ERROR);
		ft_add_token_to_list(shell, token);
	}
	return (SUCCESS);
}
