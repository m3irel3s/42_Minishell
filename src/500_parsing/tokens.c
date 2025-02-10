/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 09:52:13 by meferraz         ###   ########.fr       */
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
	size_t			i;
	size_t			start;
	size_t			op_len;
	t_token_type	type;
	char			quote_char;

	i = 0;
	quote_char = 0;
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
		{
			i++;
			continue ;
		}
		else if (ft_is_quote(shell->input[i]) && !quote_char)
		{
			quote_char = shell->input[i];
			start = i;
			i++;
			while (shell->input[i] && shell->input[i] != quote_char)
				i++;
			if (!shell->input[i])
			{
				if (ft_handle_unclosed_quote(shell, &i) == ERROR)
					return (ERROR);
			}
			else
			{
				i++;
				if (ft_create_and_add_token(shell, start, i, WORD) == ERROR)
					return ERROR;
			}
			quote_char = 0;
		}
		else if (ft_is_operator(shell->input[i]))
		{
			op_len = ft_get_operator_length(shell->input + i);
			type = ft_get_operator_type(shell->input + i, op_len);
			if (ft_create_and_add_token(shell, i, i + op_len, type) == ERROR)
				return (ERROR);
			i += op_len;
		}
		else
		{
			start = i;
			while (shell->input[i] && !ft_is_space(shell->input[i]) &&
				!ft_is_operator(shell->input[i]) && !ft_is_quote(shell->input[i]))
				i++;
			if (ft_create_and_add_token(shell, start, i, WORD) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
