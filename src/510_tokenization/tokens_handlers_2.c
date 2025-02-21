/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 14:44:11 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
					size_t *start, t_quote_info *quote_info);
static t_status	ft_handle_quote(t_shell *shell, size_t *i, size_t *start,
					t_quote_info *quote_info);

/**
 * @brief Handles a word, taking into account quotes.
 *
 * Advances the index to determine the extent of the word, taking into account
 * any quotes. If the word is quoted, it sets the quoted flag to 1 or 2,
 * respectively, and moves the index to the end of the quoted section. If the
 * quote is unmatched, it prints an error and sets the exit status to
 * EXIT_FAILURE.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the index of the start of the word in the input string.
 *
 * @return Returns ERROR if there was an error during token creation,
 *         SUCCESS otherwise.
 */
t_status	ft_handle_word(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;
	t_status		status;

	if (!shell || !i)
		return (ft_print_error(shell, ERR_INVALID_PARAMS));
	start = *i;
	ft_reset_quote_info(&quote_info);
	status = ft_process_quoted_word(shell, i, &start, &quote_info);
	if (status != SUCCESS)
		return (status);
	if (*i > start)
	{
		status = ft_create_and_add_token(shell, start, *i, quote_info.quoted);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

/**
 * @brief Process a quoted word by consuming characters while the character is
 *        not a space or an operator, or if it is within quotes.
 *
 * This function iterates through the input string, consuming characters until
 * it reaches a space or an operator, or if it is within quotes. If the quote
 * is unmatched, it prints an error and sets the exit status to EXIT_FAILURE.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i Pointer to the index of the current character in the input string.
 * @param start Pointer to the starting index of the current word in the input
 *              string.
 * @param quote_info A pointer to a structure to store the quote state,
 *                   indicating whether the section is quoted and the type of
 *                   quotes used.
 *
 * @return Returns ERROR if there was an error during token creation,
 *         SUCCESS otherwise.
 */
static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
		size_t *start, t_quote_info *quote_info)
{
	t_status status;

	while (shell->input[*i] && ((!ft_is_space(shell->input[*i])
				&& !ft_is_operator(shell->input[*i])) || quote_info->in_quotes))
	{
		status = ft_handle_quote(shell, i, start, quote_info);
		if (status != SUCCESS)
			return (status);
		(*i)++;
	}
	if (quote_info->in_quotes)
	{
		ft_print_unmatched_quote_error(shell);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Handles a quote character within a word.
 *
 * If the quote character is not enclosed within a quote, it will create a new
 * token from the last start position to the current position and reset the
 * quote information. If the quote character is enclosed within a quote, it
 * will create a new token from the start position to the current position and
 * reset the quote information.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 * @param start A pointer to the starting index of the current word.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state, including whether the current
 *                   character is within quotes and the type of quotes.
 *
 * @return Returns ERROR if there was an error during token creation,
 *         SUCCESS otherwise.
 */
static t_status	ft_handle_quote(t_shell *shell, size_t *i,
			size_t *start, t_quote_info *quote_info)
{
	t_status status;

	if (shell->input[*i] == '\'' || shell->input[*i] == '"')
	{
		if (!quote_info->in_quotes)
		{
			if (*i > *start)
			{
				status = ft_create_and_add_token(shell, *start, *i,
						quote_info->quoted);
				if (status != SUCCESS)
					return (status);
			}
			quote_info->in_quotes = 1;
			quote_info->quote_char = shell->input[*i];
			quote_info->quoted = 2 - (shell->input[*i] == '\'');
			*start = *i + 1;
		}
		else if (shell->input[*i] == quote_info->quote_char)
		{
			status = ft_create_and_add_token(shell, *start, *i,
					quote_info->quoted);
			if (status != SUCCESS)
				return (status);
			ft_reset_quote_info(quote_info);
			*start = *i + 1;
		}
	}
	return (SUCCESS);
}

void	ft_reset_quote_info(t_quote_info *quote_info)
{
	quote_info->in_quotes = 0;
	quote_info->quote_char = 0;
	quote_info->quoted = 0;
}
