/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/05 14:27:37 by meferraz         ###   ########.fr       */
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
	if (ft_tokenize_input(shell) == ERROR)
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

static t_status ft_tokenize_input(t_shell *shell)
{
	const char *input;
	char *additional_input;
	char *temp_input;

	input = shell->input;
	additional_input = NULL;
	temp_input = NULL;
	while (1)
	{
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
			if (shell->parser->quote_state == NO_QUOTE)
				break ;
			if (input[shell->parser->index] == '\0')
			{
				additional_input = readline("> ");
				if (!additional_input)
				{
					ft_putstr_fd("Error: Unmatched quotes, EOF encountered.\n", STDERR_FILENO);
					free(shell->input);
					shell->input = NULL;
					return ;
				}
				add_history(additional_input);
				temp_input = ft_strjoin(shell->input, "\n");
				free(shell->input);
				shell->input = ft_strjoin(temp_input, additional_input);
				free(temp_input);
				free(additional_input);
				input = shell->input;
				shell->parser->index = 0;
			}
		}
		if (shell->parser->quote_state == NO_QUOTE)
			break ;
	}
}
