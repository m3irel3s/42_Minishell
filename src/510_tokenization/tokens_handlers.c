/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 16:47:54 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
				t_quote_info *quote_info);
static void	ft_check_quote_state(t_shell *shell, size_t start,
				size_t *i, t_quote_info *quote_info);

/**
 * @brief Handles an operator in the input string.
 *
 * Checks if the current character is an operator and creates a new token
 * accordingly. If the character is a double operator (e.g., '&&', '||'),
 * it increments the index by 2. Otherwise, it increments the index by 1.
 * If there is an error during token creation, it sets an error status and
 * returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the index of the current character in the input string.
 * @param is_export A pointer to the flag indicating if the current context is
 * an export.
 *
 * @return Returns SUCCESS if the operator is handled successfully; otherwise,
 * returns ERROR.
 */
t_status	ft_handle_operator(t_shell *shell, size_t *i, int *is_export)
{
	size_t		start;
	t_status	status;

	if (!shell || !i || !is_export)
		return (ft_print_error(ERR_INVALID_PARAMS));
	if (*is_export)
		*is_export = 0;
	start = *i;
	if (ft_is_double_operator(shell->input + *i))
		*i += 2;
	else
		(*i)++;
	status = ft_create_and_add_token(shell, start, *i, 0);
	if (status == ERROR)
		g_exit_status = EXIT_FAILURE;
	return (status);
}

/**
 * @brief Handles an export argument in the input string.
 *
 * This function processes an export argument in the shell's input string.
 * It handles quotes within the argument and creates a token for it. If
 * unmatched quotes are found, an error is returned.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 *
 * @return Returns SUCCESS if the export argument is processed and tokenized
 *         successfully, otherwise returns ERROR.
 */

t_status	ft_handle_export_arg(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;
	t_status		status;

	if (!shell || !i)
		return (ft_print_error(ERR_INVALID_PARAMS));
	start = *i;
	ft_reset_quote_info(&quote_info);
	ft_set_export_arg_index(shell, i, &quote_info);
	if (quote_info.in_quotes != 0)
	{
		ft_print_unmatched_quote_error();
		return (ERROR);
	}
	ft_check_quote_state(shell, start, i, &quote_info);
	status = ft_create_and_add_token(shell, start, *i, quote_info.quoted);
	if (status == ERROR)
		g_exit_status = EXIT_FAILURE;
	return (status);
}

/**
 * @brief Sets the export argument index while handling quotes.
 *
 * This function iterates through the input string starting from the current
 * index, updating the index and quote information as it processes each character.
 * It tracks whether the current position is within quotes and adjusts the quote
 * information structure accordingly. The function stops iterating when it
 * encounters an unquoted space or operator.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state, indicating if inside a quote and the
 *                   type of quote.
 */

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
		t_quote_info *quote_info)
{
	while (shell->input[*i])
	{
		if (shell->input[*i] == '\'' || shell->input[*i] == '"')
		{
			if (!quote_info->quote_char)
			{
				quote_info->quote_char = shell->input[*i];
				quote_info->in_quotes++;
				quote_info->quoted = 2 - (shell->input[*i] == '\'');
			}
			else if (shell->input[*i] == quote_info->quote_char)
			{
				quote_info->in_quotes--;
				if (quote_info->in_quotes == 0)
				{
					quote_info->quote_char = 0;
					quote_info->quoted = 0;
				}
			}
		}
		else if (!quote_info->in_quotes && (ft_is_space(shell->input[*i])
				|| ft_is_operator(shell->input[*i])))
			break ;
		(*i)++;
	}
}

/**
 * @brief Checks for single and double quotes in a segment of the input string.
 *
 * This function iterates through a segment of the input string, checking for
 * single and double quotes. If it finds a single quote, it sets the `quoted`
 * field of the `t_quote_info` structure to 1. If it finds a double quote, it
 * sets the `quoted` field to 2. The function does not return any value.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param start The starting index of the segment to be checked.
 * @param i A pointer to the current index in the input string.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state, indicating if inside a quote and the
 *                   type of quote.
 */
static void	ft_check_quote_state(t_shell *shell, size_t start, size_t *i,
		t_quote_info *quote_info)
{
	while (start < *i)
	{
		if (shell->input[start] == '"')
		{
			quote_info->quoted = 2;
			start++;
			while (start < *i && shell->input[start] != '"')
				start++;
			start++;
		}
		else if (shell->input[start] == '\'')
		{
			quote_info->quoted = 1;
			start++;
			while (start < *i && shell->input[start] != '\'')
				start++;
			start++;
		}
		else
			start++;
	}
}
