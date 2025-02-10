/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 15:41:47 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status ft_handle_unclosed_quote(t_shell *shell, size_t *index);

/**
 * @brief Tokenizes the input string of the shell.
 *
 * Checks for valid input and passes control to ft_process_and_tokenize.
 * If an error occurs, the function returns ERROR. If all operations succeed,
 * the function returns SUCCESS.
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
 * @brief Processes and tokenizes the input entered by the user in the shell.
 *
 * This function processes and tokenizes the input string of the shell.
 * It iterates through the input string and checks for quotes, operators,
 * and words. If a quote is found, it processes the quoted string and
 * creates a token. If an operator is found, it creates a token. If a
 * word is found, it creates a token. If an error occurs during token
 * creation, the function returns ERROR. If all operations succeed,
 * the function returns SUCCESS.
 *
 * @param shell A pointer to the shell structure containing the input
 *              to be tokenized.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
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
				if (ft_is_command(shell->input + start, i - start))
				{
					if (ft_create_and_add_token(shell, start, i, COMMAND) == ERROR)
						return (ERROR);
				}
				else
				{
					if (ft_create_and_add_token(shell, start, i, ARGUMENT) == ERROR)
						return (ERROR);
				}
			}
			quote_char = 0;
		}
		else if (ft_is_operator(shell->input[i]))
		{
			start = i;
			while (shell->input[i] && ft_is_operator(shell->input[i]))
				i++;
			type = ft_determine_token_type(shell->input + i, start);
			if (ft_create_and_add_token(shell, i, i + start, type) == ERROR)
				return (ERROR);
			i += op_len;
		}
		else
		{
			start = i;
			while (shell->input[i] && !ft_is_space(shell->input[i]) &&
				!ft_is_operator(shell->input[i]) && !ft_is_quote(shell->input[i]))
				i++;
			if (ft_is_command(shell->input + start, i - start))
			{
				if (ft_create_and_add_token(shell, start, i, COMMAND) == ERROR)
					return (ERROR);
			}
			else
			{
				if (ft_create_and_add_token(shell, start, i, ARGUMENT) == ERROR)
					return (ERROR);
			}
		}
	}
	return (SUCCESS);
}

/**
 * @brief Handles unclosed quotes in the input string.
 *
 * If an unclosed quote is found in the input string, this function
 * reads additional input from the user until a matching quote is
 * found. It then appends the additional input to the shell's input
 * string and continues parsing from where it left off.
 *
 * @param shell A pointer to the shell structure containing the
 *              input string.
 * @param index A pointer to the index in the input string where
 *              the unclosed quote was found.
 *
 * @return Returns SUCCESS if the matching quote is found;
 *         otherwise, returns ERROR.
 */
static t_status	ft_handle_unclosed_quote(t_shell *shell, size_t *index)
{
	char *additional_input;
	char *temp;
	char quote_char;

	quote_char = shell->input[*index];
	while (1)
	{
		additional_input = readline("> ");
		if (!additional_input)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n", STDERR_FILENO);
			return (ERROR);
		}
		temp = ft_strjoin(shell->input, "\n");
		if (!temp)
		{
			free(additional_input);
			return (ERROR);
		}
		free(shell->input);
		shell->input = ft_strjoin(temp, additional_input);
		free(temp);
		free(additional_input);
		if (!shell->input)
			return (ERROR);
		while (shell->input[*index])
		{
			if (shell->input[*index] == quote_char)
			{
				(*index)++;
				return (SUCCESS);
			}
			(*index)++;
		}
	}
}
