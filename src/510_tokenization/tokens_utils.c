/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 14:44:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token_type	ft_check_single_char(t_shell *shell, char *value);
static t_token_type	ft_check_double_char(t_shell *shell, char *value);

/**
 * @brief Determines the token type for a given string.
 *
 * Checks if the string corresponds to a single or double character token
 * and returns its type. If the string is invalid, updates the shell's
 * exit_status and returns ERROR_TOKEN.
 *
 * @param shell Pointer to the shell structure for updating exit_status.
 * @param value The string to be checked.
 * @param len The length of the string to be checked.
 *
 * @return The corresponding token type or ERROR_TOKEN on failure.
 */
t_token_type	ft_determine_token_type(t_shell *shell, char *value, size_t len)
{
	if (!value)
	{
		ft_print_error(shell, ERR_NULL_TOKEN_VALUE);
		return (ERROR_TOKEN);
	}
	if (len == 1)
		return (ft_check_single_char(shell, value));
	if (len == 2)
		return (ft_check_double_char(shell, value));
	return (WORD);
}

/**
 * @brief Checks a single character and returns its corresponding token type.
 *
 * If the given string is invalid, updates the shell's exit_status and returns
 * ERROR_TOKEN.
 *
 * @param shell Pointer to the shell structure for updating exit_status.
 * @param value String to be checked.
 *
 * @return The corresponding token type or ERROR_TOKEN on failure.
 */
static t_token_type	ft_check_single_char(t_shell *shell, char *value)
{
	if (!value)
	{
		ft_print_error(shell, ERR_NULL_TOKEN_VALUE);
		return (ERROR_TOKEN);
	}
	if (*value == '|')
		return (PIPE);
	else if (*value == '<')
		return (REDIRECT_IN);
	else if (*value == '>')
		return (REDIRECT_OUT);
	return (WORD);
}

/**
 * @brief Checks a double-character string and returns its token type.
 *
 * If the given string is invalid, updates the shell's exit_status and returns
 * ERROR_TOKEN.
 *
 * @param shell Pointer to the shell structure for updating exit_status.
 * @param value The string to be checked.
 *
 * @return The corresponding token type or ERROR_TOKEN on failure.
 */
static t_token_type	ft_check_double_char(t_shell *shell, char *value)
{
	if (!value)
	{
		ft_print_error(shell, ERR_NULL_TOKEN_VALUE);
		return (ERROR_TOKEN);
	}
	if (ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	return (WORD);
}
