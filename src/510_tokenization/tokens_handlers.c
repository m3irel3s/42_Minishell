/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 11:56:24 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
				t_quote_info *quote_info);
static void	ft_check_quote_state(t_shell *shell, size_t start,
				size_t *i, t_quote_info *quote_info);

/**
 * @brief Handles an operator character in the input string.
 *
 * If the character is an operator, it creates an operator token and adds it to
 * the list of tokens. If the current context is an export, it sets the flag to
 * 0. If the operator is a double operator (e.g. ';;'), it increments the index
 * by 2. Otherwise, it increments the index by 1.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the index of the current character in the input string.
 * @param is_export Pointer to the flag indicating if the current context is an
 * export.
 *
 * @return Returns ERROR if there was an error during token creation,
 *         SUCCESS otherwise.
 */
t_status	ft_handle_operator(t_shell *shell, size_t *i, int *is_export)
{
	size_t		start;
	t_status	status;

	if (!shell || !i || !is_export)
	{
		ft_printf(STDERR_FILENO, ERR_INVALID_PARAMS);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	if (*is_export)
		*is_export = 0;
	start = *i;
	if (ft_is_double_operator(shell->input + *i))
		*i += 2;
	else
		(*i)++;
	status = ft_create_and_add_token(shell, start, *i, 0);
	if (status == ERROR)
		shell->exit_status = EXIT_FAILURE;
	return (status);
}

/**
 * @brief Handles an export argument.
 *
 * Advances the index to determine the extent of the export argument, taking
 * into account any quotes. If the argument is quoted, it sets the quoted flag
 * to 1 or 2, respectively, and moves the index to the end of the quoted
 * section. If the quote is unmatched, it prints an error and sets the exit
 * status to EXIT_FAILURE.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the index of the start of the export argument in the
 * input string.
 *
 * @return Returns ERROR if there was an error during token creation,
 *         SUCCESS otherwise.
 */
t_status	ft_handle_export_arg(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;
	t_status		status;

	if (!shell || !i)
	{
		ft_printf(STDERR_FILENO, ERR_INVALID_PARAMS);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	start = *i;
	ft_reset_quote_info(&quote_info);
	ft_set_export_arg_index(shell, i, &quote_info);
	if (quote_info.in_quotes != 0)
	{
		ft_print_unmatched_quote_error(shell);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	ft_check_quote_state(shell, start, i, &quote_info);
	status = ft_create_and_add_token(shell, start, *i, quote_info.quoted);
	if (status == ERROR)
		shell->exit_status = EXIT_FAILURE;
	return (status);
}

/**
 * @brief Advances the index to determine the extent of an export argument.
 *
 * This function iterates over the input string starting from the current
 * index, updating the quote information as it encounters quote characters.
 * It increments the index until it reaches the end of the input, a space,
 * updating the quote information structure with the current quote character,
 * whether the index is within quotes, and the type of quotes encountered.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will
 *          be incremented as the function processes characters.
 * @param quote_info A pointer to a structure holding information about the
 *                   current quote state, including whether the current
 *                   character is within quotes and the type of quotes.
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
 * @brief Determines the quote state within a given range of the input string.
 *
 * This function iterates through the input string from the provided start index
 * up to the index pointed to by `i`, checking for occurrences of single or
 * double quotes. It updates the quote information structure based on the type
 * of quotes encountered, marking whether the section is quoted and if it's
 * enclosed by single or double quotes.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param start The starting index to check for quotes in the input string.
 * @param i A pointer to the current index in the input string, marking the
 *          end of the range to check for quotes.
 * @param quote_info A pointer to a structure to store the quote state,
 *                   indicating whether the section is quoted and the type of
 *                   quotes used.
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
