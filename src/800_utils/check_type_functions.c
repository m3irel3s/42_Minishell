/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:55:14 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 13:36:54 by jmeirele         ###   ########.fr       */
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

/**
 * @brief Checks if a character is a quote.
 *
 * Determines if the given character is a single or double quote.
 *
 * @param c Character to be checked.
 *
 * @return 1 if the character is a quote, 0 otherwise.
 */

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/**
 * @brief Checks if a given value is a valid command.
 *
 * Checks if the given string, up to the given length, is a valid command.
 *
 * @param value String to be checked.
 * @param len Length of the string to be checked.
 *
 * @return 1 if the string is a valid command, 0 otherwise.
 *
 * The following commands are considered valid:
 * - echo
 * - cd
 * - pwd
 * - export
 * - unset
 * - env
 * - exit
 */
int	ft_is_command(char *value, size_t len)
{
	if (!value)
		return (ERROR);
	if ((len == 4 && strncmp(value, "echo", 4) == 0)
		|| (len == 2 && strncmp(value, "cd", 2) == 0)
		|| (len == 3 && strncmp(value, "pwd", 3) == 0)
		|| (len == 6 && strncmp(value, "export", 6) == 0)
		|| (len == 5 && strncmp(value, "unset", 5) == 0)
		|| (len == 3 && strncmp(value, "env", 3) == 0)
		|| (len == 4 && strncmp(value, "exit", 4) == 0))
		return (SUCCESS);
	else
		return (ERROR);
}
