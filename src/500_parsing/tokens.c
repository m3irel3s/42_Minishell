/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 09:46:18 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status ft_handle_unclosed_quote(t_shell *shell, const char **input,
		char **additional_input, char **temp_input);
/**
 * @brief Tokenizes the input entered by the user in the shell.
 *
 * This function first checks if the shell and its input are valid.
 * If not, it returns ERROR. Then, it calls the function
 * ft_process_and_tokenize, which processes and tokenizes the input.
 * If this function returns ERROR, ft_tokenize also returns ERROR.
 * If all operations succeed, it returns SUCCESS.
 *
 * @param shell A pointer to the shell structure containing the input
 *              to be tokenized.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
 */
int	ft_tokenize(t_shell *shell)
{
	if (!shell || !shell->input)
		return (ERROR);
	return (ft_process_and_tokenize(shell));
}

/**
 * @brief Processes and tokenizes the shell's input.
 *
 * This function iterates over the input string in the shell structure,
 * handling different parser states and managing quotes. It processes
 * each character according to the current state and transitions states
 * as necessary. If an unclosed quote is detected at the end of the input,
 * it prompts for additional input until the quote is closed or an error
 * occurs. If successful, it ensures that any remaining input segment is
 * tokenized before returning.
 *
 * @param shell A pointer to the shell structure containing the input
 *              and parser state to be processed and tokenized.
 *
 * @return Returns SUCCESS if the input is successfully processed and
 *         tokenized; otherwise, returns ERROR.
 */

static t_status	ft_process_and_tokenize(t_shell *shell)
{
	const char *input;
	char *additional_input;
	char *temp_input;

	input = shell->input;
	additional_input = NULL;
	temp_input = NULL;
	shell->parser->start = 0;
	shell->parser->index = 0;
	while (1)
	{
		while (input[shell->parser->index])
		{
			ft_handle_current_state(shell);
			shell->parser->index++;
			if (shell->parser->quote_state != NO_QUOTE && input[shell->parser->index] == '\0')
			{
				if (ft_handle_unclosed_quote(shell, &input, &additional_input, &temp_input) == ERROR)
					return (ERROR);
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

/**
 * @brief Handles an unclosed quote in the input string by prompting the user
 *        for additional input and appending it to the original input string.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and the parser state to be updated.
 * @param input A pointer to the input string to be updated.
 * @param additional_input A pointer to the additional input string to be read
 *                         from the user.
 * @param temp_input A pointer to a temporary string used to store the
 *                   concatenated strings.
 *
 * @return Returns SUCCESS if the additional input is successfully read and
 *         appended to the original input string; otherwise, returns ERROR.
 */
static t_status	ft_handle_unclosed_quote(t_shell *shell, const char **input, char **additional_input, char **temp_input)
{
	*additional_input = readline("> ");
	if (!*additional_input)
	{
		ft_putstr_fd("Error: Unmatched quotes, EOF encountered.\n", STDERR_FILENO);
		free(shell->input);
		shell->input = NULL;
		return (ERROR);
	}
	add_history(*additional_input);
	*temp_input = ft_strjoin(shell->input, "\n");
	free(shell->input);
	shell->input = ft_strjoin(*temp_input, *additional_input);
	free(*temp_input);
	free(*additional_input);
	*input = shell->input;
	shell->parser->index = 0;
	return (SUCCESS);
}
