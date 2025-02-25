/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/25 17:09:58 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token_type	ft_check_single_char(char *value);
static t_token_type	ft_check_double_char(char *value);

/**
 * @brief Determines the token type for a given token string.
 *
 * Checks if the token corresponds to a single or double character operator,
 * and returns its type. For any other length, it returns WORD.
 *
 * @param value The token string.
 * @param len The length of the token string.
 * @return The corresponding token type, or ERROR_TOKEN on error.
 */
t_token_type	ft_determine_token_type(char* og_value, char *value, size_t len)
{
	if (!value)
	{
		ft_print_error(ERR_NULL_TOKEN_VALUE);
		return (ERROR_TOKEN);
	}
	if (ft_strncmp(og_value, value, ft_strlen(og_value)) != 0)
		return (WORD);
	if (len == 1)
		return (ft_check_single_char(value));
	if (len == 2)
		return (ft_check_double_char(value));
	return (WORD);
}

/**
 * @brief Checks a single-character token and returns its type.
 *
 * @param value The token string.
 * @return The token type (PIPE, REDIRECT_IN, REDIRECT_OUT, or WORD).
 */
static t_token_type	ft_check_single_char(char *value)
{
	if (!value)
	{
		ft_print_error(ERR_NULL_TOKEN_VALUE);
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
 * @brief Checks a double-character token and returns its type.
 *
 * @param value The token string.
 * @return The token type (HEREDOC, REDIRECT_APPEND, or WORD).
 */
static t_token_type	ft_check_double_char(char *value)
{
	if (!value)
	{
		ft_print_error(ERR_NULL_TOKEN_VALUE);
		return (ERROR_TOKEN);
	}
	if (ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	return (WORD);
}
