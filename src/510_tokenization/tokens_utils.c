/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 09:55:33 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token_type	ft_check_single_char(char *value);
static t_token_type	ft_check_double_char(char *value);

/**
 * @brief Checks the given string and returns its corresponding token type.
 *
 * Checks the given string and returns its corresponding token type.
 * If the string is a single character, checks for single character tokens.
 * If the string is two characters long, checks for double character tokens.
 * If the string does not match any special tokens, returns WORD.
 *
 * @param value The string to be checked.
 * @param len The length of the string to be checked.
 *
 * @return Returns the corresponding token type.
 */
t_token_type	ft_determine_token_type(char *value, size_t len)
{
	if (len == 1)
		return (ft_check_single_char(value));
	if (len == 2)
		return (ft_check_double_char(value));
	return (WORD);
}

/**
 * @brief Checks a single character and returns its corresponding token type.
 *
 * Checks if the given string is a single character and if it is a special
 * character, returns its corresponding token type. If not, returns WORD.
 *
 * @param value String to be checked.
 *
 * @return Returns the corresponding token type.
 */
static t_token_type	ft_check_single_char(char *value)
{
	if (*value == '|')
		return (PIPE);
	else if (*value == '<')
		return (REDIRECT_IN);
	else if (*value == '>')
		return (REDIRECT_OUT);
	return (WORD);
}

/**
 * @brief Checks the given string and returns its corresponding token type.
 *
 * Checks the given string and returns its corresponding token type.
 * If the string is two characters long, checks for double character tokens.
 * If the string does not match any special tokens, returns WORD.
 *
 * @param value The string to be checked.
 *
 * @return Returns the corresponding token type.
 */
static t_token_type	ft_check_double_char(char *value)
{
	if (ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	return (WORD);
}
