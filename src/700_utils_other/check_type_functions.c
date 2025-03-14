/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:55:14 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/14 17:12:39 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Checks if a character is a shell operator.
 *
 * Checks if a character is a valid shell operator, i.e., either a pipe '|',
 * redirection '<' or '>', or an ampersand '&'.
 *
 * @param c Character to be checked.
 *
 * @return 1 if the character is an operator, 0 otherwise.
 */
bool	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Checks if a string is a double shell operator.
 *
 * Checks if a given string is either "<<" or ">>".
 *
 * @param str String to be checked.
 *
 * @return 1 if the string is a double operator, 0 otherwise.
 */
bool	ft_is_double_operator(char *str)
{
	return (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0);
}

/**
 * @brief Checks if a character is a whitespace.
 *
 * @param c Character to be checked.
 *
 * @return 1 if the character is a whitespace, 0 otherwise.
 *
 * The considered whitespace characters are:
 * - Space (32)
 * - Horizontal tab (9)
 * - Vertical tab (11)
 * - Form feed (12)
 * - Carriage return (13)
 */
bool	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
