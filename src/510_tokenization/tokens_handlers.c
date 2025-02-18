/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 15:38:09 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
				t_quote_info *quote_info);
static void	ft_check_quote_state(t_shell shell, size_t start,
				size_t *i, t_quote_info *quote_info);

/**
 * @brief Handles operators in the input by creating a token for them.
 * If a double operator is found, it increments the index by 2, otherwise
 * by 1. It also resets the export flag if it is set.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the current index in the input string.
 * @param is_export Pointer to the flag indicating if the current context is
 * an export.
 * @return SUCCESS if the token is created and added successfully, ERROR
 * otherwise.
 */

t_status	ft_handle_operator(t_shell *shell, size_t *i, int *is_export)
{
	size_t	start;

	if (*is_export)
		*is_export = 0;
	start = *i;
	if (ft_is_double_operator(shell->input + *i))
		*i += 2;
	else
		(*i)++;
	return (ft_create_and_add_token(shell, start, *i, 0));
}

/**
 * @brief Handles an export argument in the input by creating a token for it.
 *
 * It first sets the index to the end of the argument by calling
 * ft_set_export_arg_index. Then it checks if the argument had unmatched quotes
 * and prints an error message if so. Finally, it creates a token with the
 * argument and adds it to the shell's token list.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the current index in the input string.
 * @return SUCCESS if the token is created and added successfully, ERROR
 * otherwise.
 */
t_status	ft_handle_export_arg(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;

	start = *i;
	quote_info.in_quotes = 0;
	quote_info.quote_char = 0;
	quote_info.quoted = 0;
	ft_set_export_arg_index(shell, i, &quote_info);
	if (quote_info.in_quotes != 0)
		return (ft_print_unmatched_quote_error());
	ft_check_quote_state(*shell, start, i, &quote_info);
	return (ft_create_and_add_token(shell, start, *i, quote_info.quoted));
}

/**
 * @brief Sets the index to the end of the current export argument.
 *
 * This function iterates through the input string from the current index
 * until it finds a space or an operator while not inside quotes. If it
 * encounters a quote, it increments or decrements the quote count
 * accordingly. If the quote count reaches 0, it resets the quote character
 * and quoted flag.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the current index in the input string.
 * @param quote_info Pointer to a structure containing information about the
 *                   current quote state.
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
 * @brief Updates the quote state in the quote information structure.
 *
 * This function goes through the input string from the start index to the
 * current index, and updates the quote state in the quote information structure
 * accordingly. If it encounters a quote, it increments or decrements the quote
 * count accordingly. If the quote count reaches 0, it resets the quote character
 * and quoted flag.
 *
 * @param shell The shell struct containing the input string.
 * @param start The starting index of the substring to be processed.
 * @param i Pointer to the current index in the input string.
 * @param quote_info Pointer to a structure containing information about the
 *                   current quote state.
 */
static void	ft_check_quote_state(t_shell shell, size_t start, size_t *i,
		t_quote_info *quote_info)
{
	while (start < *i)
	{
		if (shell.input[start] == '"')
		{
			quote_info->quoted = 2;
			start++;
			while (shell.input[start] != '"')
				start++;
			start++;
		}
		else if (shell.input[start] == '\'')
		{
			quote_info->quoted = 1;
			start++;
			while (shell.input[start] != '\'')
				start++;
			start++;
		}
		else
			start++;
	}
}
