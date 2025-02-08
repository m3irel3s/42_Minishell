/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_type_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:55:14 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/08 16:13:35 by meferraz         ###   ########.fr       */
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
int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
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
int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
