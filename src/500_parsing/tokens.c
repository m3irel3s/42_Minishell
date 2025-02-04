/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 16:17:45 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static t_status ft_process_and_tokenize(t_shell *shell)
{
	const char *input = shell->input;
    size_t start = 0;
    size_t i = 0;
    t_token *token;

    while (i <= shell->parser->index)
    {
        if (shell->parser->state == STATE_GENERAL)
        {
            if (ft_is_space(input[i]))
                start = ++i;
            else
            {
                shell->parser->state = ft_is_operator(input[i]) ? STATE_IN_OPERATOR : STATE_IN_WORD;
                shell->parser->token_count++;
                start = i;
            }
        }
        else if (shell->parser->quote_state != NO_QUOTE || shell->parser->state == STATE_IN_WORD)
        {
            if ((shell->parser->quote_state == NO_QUOTE && ft_is_space(input[i])) ||
                (shell->parser->quote_state != NO_QUOTE && input[i] == '\'' && shell->parser->quote_state == SINGLE_QUOTE) ||
                (shell->parser->quote_state != NO_QUOTE && input[i] == '"' && shell->parser->quote_state == DOUBLE_QUOTE))
            {
                token = ft_create_token(strndup(input + start, i - start), ft_determine_token_type(strndup(input + start, i - start)));
                ft_add_token_to_list(shell, token);
                shell->parser->state = STATE_GENERAL;
                shell->parser->quote_state = NO_QUOTE;
                start = i + 1;
            }
        }
        else if (shell->parser->state == STATE_IN_OPERATOR)
        {
            if (!ft_is_operator(input[i]) || (i > 0 && input[i] != input[i - 1]))
            {
                token = ft_create_token(strndup(input + start, i - start), ft_determine_token_type(strndup(input + start, i - start)));
                ft_add_token_to_list(shell, token);
                shell->parser->state = STATE_GENERAL;
                start = i;
            }
        }
        i++;
    }
    // Handle any remaining text
    if (i > start)
    {
        token = ft_create_token(strndup(input + start, i - start), ft_determine_token_type(strndup(input + start, i - start)));
        ft_add_token_to_list(shell, token);
    }
    return (SUCCESS);
}
