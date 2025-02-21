/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 08:53:01 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
					size_t *start, t_quote_info *quote_info);
static t_status	ft_handle_quote(t_shell *shell, size_t *i, size_t *start,
					t_quote_info *quote_info);
static void		ft_reset_quote_info(t_quote_info *quote_info);

/**
 * @brief Processes a word in the input string, handling any quotes.
 *
 * This function initializes quote information and processes a word in the
 * input string, taking into account quoted sections. It creates and adds a
 * token for the word if successful. If there is an error in processing, it
 * sets the shell's exit status to EXIT_FAILURE and returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 *
 * @return Returns ERROR if there was an error during processing,
 *         SUCCESS otherwise.
 */

t_status	ft_handle_word(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;

	if (!shell || !i)
	{
		ft_printf(STDERR_FILENO, ERR_INVALID_PARAMS);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	start = *i;
	ft_reset_quote_info(&quote_info);
	if (ft_process_quoted_word(shell, i, &start, &quote_info) != SUCCESS)
		return (shell->exit_status = EXIT_FAILURE, ERROR);
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i,
				quote_info.quoted) != SUCCESS)
			return (shell->exit_status = EXIT_FAILURE, ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Processes a section of the input string, handling quoted words.
 *
 * This function iterates through the input string starting from the current
 * index, processing characters until it encounters a space, an operator, or
 * the end of a quoted section. It updates the index and quote information
 * during processing. If a quoted section is not properly closed, it sets the
 * shell's exit status to EXIT_FAILURE and returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 * @param start A pointer to the starting index of the current word or quoted
 *              section in the input.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state, indicating if inside a quote and the
 *                   type of quote.
 *
 * @return Returns ERROR if there was an unmatched quote or if there was an
 *         error during quote handling; otherwise, returns SUCCESS.
 */

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
		size_t *start, t_quote_info *quote_info)
{
	while (shell->input[*i] && ((!ft_is_space(shell->input[*i])
				&& !ft_is_operator(shell->input[*i])) || quote_info->in_quotes))
	{
		if (ft_handle_quote(shell, i, start, quote_info) != SUCCESS)
		{
			shell->exit_status = EXIT_FAILURE;
			return (ERROR);
		}
		(*i)++;
	}
	if (quote_info->in_quotes)
	{
		ft_print_unmatched_quote_error(shell);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Handles a quote in the input string.
 *
 * If the current character is a single or double quote, this function
 * checks if the quote is the start of a new quoted section or the end
 * of an existing one. It updates the quote information structure and
 * creates a new token if the quote is the end of a quoted section.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 * @param start A pointer to the starting index of the current word or quoted
 *              section in the input.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state, indicating if inside a quote and the
 *                   type of quote.
 *
 * @return Returns ERROR if there was an error during quote handling;
 *         otherwise, returns SUCCESS.
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
					return (shell->exit_status = EXIT_FAILURE, ERROR);
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
				return (shell->exit_status = EXIT_FAILURE, ERROR);
			ft_reset_quote_info(quote_info);
			*start = *i + 1;
		}
	}
	return (SUCCESS);
}

/**
 * @brief Resets the quote information structure to its default state.
 *
 * This function clears any existing quote state by setting the `in_quotes`,
 * `quote_char`, and `quoted` fields of the `t_quote_info` structure to zero.
 * It is typically used to reinitialize the structure before processing a new
 * segment of the input string.
 *
 * @param quote_info A pointer to the `t_quote_info` structure to be reset.
 */

static void	ft_reset_quote_info(t_quote_info *quote_info)
{
	quote_info->in_quotes = 0;
	quote_info->quote_char = 0;
	quote_info->quoted = 0;
}
