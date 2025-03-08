/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:16:04 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 15:17:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_check_redirect_operator(char *input, int i);

/**
 * @brief Validates the use of redirection operators in the input string.
 *
 * This function checks the input string for invalid use of redirection operators,
 * such as having consecutive redirection operators, or having a redirection
 * operator with no file name specified.
 *
 * @param input The input string to be validated.
 * @return SUCCESS if the input string is valid, ERROR otherwise.
 */
t_status	ft_validate_redirects(char *input)
{
	int	i;
	int	new_index;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (ft_skip_quotes(input, &i, input[i]) == ERROR)
				return (ERROR);
			continue ;
		}
		if (input[i] == '<' || input[i] == '>')
		{
			new_index = ft_check_redirect_operator(input, i);
			if (new_index == -1)
				return (ERROR);
			i = new_index;
		}
		else
			i++;
	}
	return (SUCCESS);
}

/**
 * @brief Checks the validity of a redirection operator and advances the index.
 *
 * This function examines the input string starting at the given index `i`
 * to determine the length of a redirection operator ('<' or '>') and skips
 * over any subsequent whitespace. It ensures that a valid token follows the
 * redirection operator, returning the new index if valid or -1 if an error
 * is encountered, such as consecutive operators or a missing target.
 *
 * @param input The input string containing the redirection operator.
 * @param i The current index in the input string.
 * @return The index of the character following the valid redirection operator
 * and any whitespace, or -1 if an error is detected.
 */
static int	ft_check_redirect_operator(char *input, int i)
{
	int	operator_len;

	operator_len = 1;
	if (input[i + 1] == input[i])
		operator_len = 2;
	i += operator_len;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (!input[i] || ft_strchr("<>|", input[i]))
	{
		if (!input[i])
			ft_print_syntax_error("newline");
		else
			ft_print_syntax_error(&input[i]);
		return (-1);
	}
	return (i);
}
