/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/05 14:47:50 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status ft_process_and_tokenize(t_shell *shell);


/**
 * @brief Tokenizes the input string by processing escaped characters and
 *        creating tokens from the input string.
 *
 * This function tokenizes the input string by calling
 * ft_process_and_tokenize(). If the tokenization succeeds, it returns SUCCESS;
 * otherwise, it returns ERROR.
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
	if (ft_process_and_tokenize(shell) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Processes the input string by adding escaped characters to the parser's
 *        index and tokenize it by creating tokens from the input string.
 *
 * This function processes the input string by adding escaped characters to the
 * parser's index. Then, if the parser is not in a quote state, it allocates
 * memory for the tokens list and populates it with tokens created from the
 * input string. If the parser encounters an EOF while in a quote state, it
 * reads additional input from the user and appends it to the input string.
 *
 * @param shell A pointer to the shell structure whose input string is to be
 *              processed and tokenized.
 *
 * @return SUCCESS if the tokenization succeeds, ERROR otherwise.
 */
static t_status ft_process_and_tokenize(t_shell *shell)
{
	const char *input;
	char *additional_input;
	char *temp_input;

	input = shell->input;
	additional_input = NULL;
	temp_input = NULL;
	shell->parser->start = 0;
	while (1)
	{
		while (input[shell->parser->index])
		{
			if (shell->parser->state == STATE_GENERAL)
				ft_handle_general_state(shell);
			else if (shell->parser->quote_state != NO_QUOTE)
				ft_handle_quote_state(shell);
			else if (shell->parser->state == STATE_IN_WORD)
				ft_handle_word_state(shell);
			else if (shell->parser->state == STATE_IN_OPERATOR)
				ft_handle_operator_state(shell);
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
					return (ERROR);
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
	if (shell->parser->state != STATE_GENERAL && shell->parser->index > shell->parser->start)
	{
		if (ft_create_and_add_token(shell, shell->parser->start, shell->parser->index) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
