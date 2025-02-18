/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 15:37:06 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
					size_t *start, t_quote_info *quote_info);
static t_status	ft_handle_quote(t_shell *shell, size_t *i, size_t *start,
					t_quote_info *quote_info);
static void		ft_reset_quote_info(t_quote_info *quote_info);

/**
 * @brief Handles a word in the input, including quoted parts.
 * If the word has quoted parts, it will be split into multiple tokens.
 * If the word has unquoted parts, it will be split into multiple tokens.
 * @param shell The shell struct.
 * @param i The index of the current character in the input string.
 * @return ERROR if there was an error during token creation,
 *         SUCCESS otherwise.
 */
t_status	ft_handle_word(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;

	start = *i;
	ft_reset_quote_info(&quote_info);
	if (ft_process_quoted_word(shell, i, &start, &quote_info) != SUCCESS)
		return (ERROR);
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i,
				quote_info.quoted) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Processes a word in the input string, handling quoted parts.
 *
 * This function iterates through the input string from the current index,
 * processing characters until a space or operator is found, unless the
 * current characters are within quotes. It uses the quote information to
 * track and manage quoted sections. If an unmatched quote is detected,
 * it returns an error.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will
 *          be updated as the function processes characters.
 * @param start A pointer to the start index of the current word being
 *              processed, which is updated when a quoted section is handled.
 * @param quote_info A pointer to a structure holding information about
 *                   the current quote state.
 *
 * @return Returns SUCCESS if the word is processed without error; otherwise,
 *         returns ERROR if an unmatched quote is detected or if processing
 *         fails.
 */

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
		size_t *start, t_quote_info *quote_info)
{
	while (shell->input[*i] && ((!ft_is_space(shell->input[*i])
				&& !ft_is_operator(shell->input[*i])) || quote_info->in_quotes))
	{
		if (ft_handle_quote(shell, i, start, quote_info) != SUCCESS)
			return (ERROR);
		(*i)++;
	}
	if (quote_info->in_quotes)
		return (ft_print_unmatched_quote_error());
	return (SUCCESS);
}

/**
 * @brief Handles quotes in the input string, managing quoted state.
 *
 * This function checks if the current character is a quote. If it is,
 * and the quote is not currently open, it finalizes the token preceding
 * the quote, updates the quote state, and marks the start index for the
 * next token. If the quote is already open and matches the current quote
 * character, it finalizes the quoted token, resets the quote state, and
 * updates the start index for the next token.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 * @param start A pointer to the start index of the current token or quoted
 *              section being processed.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state.
 *
 * @return Returns SUCCESS if quote handling is successful; otherwise,
 *         returns ERROR if token creation fails.
 */

static t_status	ft_handle_quote(t_shell *shell, size_t *i,
			size_t *start, t_quote_info *quote_info)
{
	if (shell->input[*i] == '\'' || shell->input[*i] == '"')
	{
		if (!quote_info->in_quotes)
		{
			if (*i > *start)
			{
				if (ft_create_and_add_token(shell, *start, *i,
						quote_info->quoted) != SUCCESS)
					return (ERROR);
			}
			quote_info->in_quotes = 1;
			quote_info->quote_char = shell->input[*i];
			quote_info->quoted = 2 - (shell->input[*i] == '\'');
			*start = *i + 1;
		}
		else if (shell->input[*i] == quote_info->quote_char)
		{
			if (ft_create_and_add_token(shell, *start, *i,
					quote_info->quoted) != SUCCESS)
				return (ERROR);
			ft_reset_quote_info(quote_info);
			*start = *i + 1;
		}
	}
	return (SUCCESS);
}

/**
 * @brief Resets the quote information to its initial state.
 *
 * This function resets the quote information struct to its initial state, with
 * all fields set to 0. It is used after a quoted section has been processed to
 * reset the quote state for the next section.
 *
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state.
 */
static void	ft_reset_quote_info(t_quote_info *quote_info)
{
	quote_info->in_quotes = 0;
	quote_info->quote_char = 0;
	quote_info->quoted = 0;
}
