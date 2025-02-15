/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:32:14 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/15 09:22:27 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_close_quote(t_shell *shell, size_t *index,
					size_t *token_start, int *is_quoted);
static t_status	ft_handle_quote_encounter(t_shell *shell,
					size_t *index, size_t *token_start, int *is_quoted);
static t_status	ft_process_word_quotes(t_shell *shell,
					size_t *index, size_t *token_start, int *is_quoted);
static t_status	ft_process_word(t_shell *shell, size_t *index);

/**
 * @brief Handles the processing of a word token in the input string.
 *
 * This function checks if the current word token starts with "export" and is
 * followed by a space or end of input. If so, it sets the is_export_flag,
 * advances the index, and creates a token for the "export" keyword. Otherwise,
 * it processes the word token according to whether the is_export_flag is set.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and tokens.
 * @param index A pointer to the current index in the input string.
 * @param is_export_flag A pointer to a flag indicating whether the current
 *                       token is part of an export command.
 *
 * @return Returns SUCCESS if the word token is successfully processed;
 *         otherwise, returns ERROR.
 */

t_status	ft_handle_word(t_shell *shell, size_t *index,
		int *is_export_flag)
{
	size_t	token_start;

	token_start = *index;
	if (ft_strncmp(shell->input + *index, "export", 6) == 0)
	{
		if (ft_is_space(shell->input[*index + 6])
			|| shell->input[*index + 6] == '\0')
		{
			*is_export_flag = 1;
			*index += 6;
			return (ft_create_and_add_token(shell, token_start, *index, 0));
		}
	}
	if (*is_export_flag)
		return (ft_handle_export_token(shell, index));
	else
		return (ft_process_word(shell, index));
}

/**
 * @brief Handles the closing of a quote in a word token.
 *
 * This function checks if there is a token to create between the current index
 * and the token start index. If so, it creates a token for the substring
 * between the indices and adds it to the shell's token list. It then sets the
 * is_quoted flag to 0 and sets the token start index to the current index plus
 * 1.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and tokens.
 * @param index A pointer to the current index in the input string.
 * @param token_start A pointer to the starting index of the current word token.
 * @param is_quoted A pointer to the is_quoted flag indicating whether the
 *                  current token is inside a quote.
 *
 * @return Returns SUCCESS if the token is successfully created and added to
 *         the shell's token list; otherwise, returns ERROR.
 */
static t_status	ft_close_quote(t_shell *shell, size_t *index,
		size_t *token_start, int *is_quoted)
{
	if (*index > *token_start)
	{
		if (ft_create_and_add_token(shell, *token_start, *index, 0) != SUCCESS)
			return (ERROR);
	}
	*is_quoted = 0;
	*token_start = *index + 1;
	return (SUCCESS);
}

/**
 * @brief Handles the encounter of a quote character in the input string.
 *
 * This function checks if a quote character is encountered in the input
 * string and updates the token list accordingly. If the current index
 * is greater than the token start, it creates a token for the substring
 * between token_start and the current index. If the is_quoted flag is
 * not set, it sets the flag and updates the token_start to the index
 * after the quote character. If the quote character matches the initial
 * quote character, it calls ft_close_quote to handle the closing of the
 * quote.
 *
 * @param shell A pointer to the shell structure containing the input
 *              string and tokens.
 * @param index A pointer to the current index in the input string.
 * @param token_start A pointer to the starting index of the current
 *                    word token.
 * @param is_quoted A pointer to the is_quoted flag indicating whether
 *                  the current token is inside a quote.
 *
 * @return Returns SUCCESS if the token is successfully created and
 *         added to the shell's token list or if the quote is handled
 *         correctly; otherwise, returns ERROR.
 */

static t_status	ft_handle_quote_encounter(t_shell *shell,
		size_t *index, size_t *token_start, int *is_quoted)
{
	char	quote_char;

	quote_char = shell->input[*index];
	if (*index > *token_start)
	{
		if (ft_create_and_add_token(shell, *token_start,
				*index, 0) != SUCCESS)
			return (ERROR);
	}
	if (!*is_quoted)
	{
		*is_quoted = 1;
		*token_start = *index + 1;
	}
	else if (shell->input[*index] == quote_char)
	{
		if (ft_close_quote(shell, index, token_start,
				is_quoted) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Handles the processing of quotes in a word token.
 *
 * This function processes any quotes it encounters in the word token by either
 * creating a new token for the substring before the quote or closing an open
 * quote. It then advances the index to the next character.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and tokens.
 * @param index A pointer to the current index in the input string.
 * @param token_start A pointer to the starting index of the current word token.
 * @param is_quoted A pointer to the is_quoted flag indicating whether the
 *                  current token is inside a quote.
 *
 * @return Returns SUCCESS if the quotes are successfully processed;
 *         otherwise, returns ERROR.
 */
static t_status	ft_process_word_quotes(t_shell *shell,
		size_t *index, size_t *token_start, int *is_quoted)
{
	while (shell->input[*index] && !ft_is_space(shell->input[*index])
		&& !ft_is_operator(shell->input[*index]))
	{
		if (shell->input[*index] == '\'' || shell->input[*index] == '"')
		{
			if (ft_handle_quote_encounter(shell, index, token_start,
					is_quoted) != SUCCESS)
				return (ERROR);
		}
		(*index)++;
	}
	return (SUCCESS);
}

/**
 * @brief Processes a word token by handling quotes and creating tokens.
 *
 * This function processes a word token in the shell's input string. It
 * detects and handles any quotes within the token, creating new tokens
 * for substrings as necessary. If an unmatched quote is found, it outputs
 * a syntax error message. Once processing is complete, the function creates
 * a new token for the processed word segment if it has a length greater than
 * zero and adds it to the shell's token list.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and tokens.
 * @param index A pointer to the current index in the input string.
 *
 * @return Returns SUCCESS if the word token is successfully processed;
 *         otherwise, returns ERROR.
 */

/**
 * @brief Processes a word token in the shell's input string.
 *
 * This function processes a word token by handling any quotes within the token.
 * It uses ft_process_word_quotes to manage the quotes and create tokens for
 * substrings as necessary. If an unmatched quote is detected, an error message
 * is printed and the function returns ERROR. If the word segment has a length
 * greater than zero after processing, a new token is created and added to the
 * shell's token list.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and tokens.
 * @param index A pointer to the current index in the input string.
 *
 * @return Returns SUCCESS if the word token is successfully processed;
 *         otherwise, returns ERROR.
 */

static t_status	ft_process_word(t_shell *shell, size_t *index)
{
	size_t	token_start;
	int		is_quoted;

	token_start = *index;
	is_quoted = 0;
	if (ft_process_word_quotes(shell, index, &token_start,
			&is_quoted) != SUCCESS)
		return (ERROR);
	if (is_quoted)
	{
		ft_putstr_fd("minishell: syntax error: unmatched quote\n", 2);
		return (ERROR);
	}
	if (*index > token_start)
	{
		if (ft_create_and_add_token(shell, token_start,
				*index, 0) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
