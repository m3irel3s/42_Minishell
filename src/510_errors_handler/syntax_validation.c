/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_remove_spaces(char *str);
static t_status	ft_check_quotes(char *input);
static t_status	ft_skip_quotes(char *input, int *i, char quote);
static t_status ft_validate_pipes(char *input);
static t_status	ft_validate_redirects(char *input);

/**
 * @brief Removes leading and trailing spaces from a string.
 * @param str The string to have its spaces removed.
 * @note This function is not thread-safe.
 */
static void	ft_remove_spaces(char *str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	j = 0;
	if (i > 0)
	{
		while (str[j + i])
		{
			str[j] = str[j + i];
			j++;
		}
		str[j] = '\0';
	}
	i = ft_strlen(str);
	while (i > 0 && ft_is_space(str[i - 1]) == 1)
		i--;
	str[i] = '\0';
}

/**
 * @brief Checks if all quotes are properly closed in the input string.
 * @param input The input string to be checked.
 * @return SUCCESS if all quotes are properly closed, ERROR otherwise.
 */
static t_status	ft_check_quotes(char *input)
{
	size_t	i;
	char	quote_char;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote_char = input[i];
			i++;
			while (input[i] && input[i] != quote_char)
				i++;
			if (input[i] != quote_char)
				return (ERROR);
			i++;
		}
		else
			i++;
	}
	return (SUCCESS);
}

/**
 * @brief Skips over a quoted section in the input string.
 *
 * @param input The input string containing the quoted section to be skipped.
 * @param i A pointer to the current index in the input string.
 * @param quote The quote character to be looked for.
 * @return SUCCESS if the quote is matched, or an error status if there
 * is an unmatched quote.
 */
static t_status	ft_skip_quotes(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (ft_print_unmatched_quote_error());
	(*i)++;
	return (SUCCESS);
}

/**
 * @brief Validates the use of pipes in the input string.
 *
 * This function checks the input string for invalid use of pipes, such as
 * starting or ending with a pipe, or having consecutive pipes.
 *
 * @param input The input string to be validated.
 * @return SUCCESS if the input string is valid, or an error status otherwise.
 */
static t_status ft_validate_pipes(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
		return (ERROR);
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (ft_skip_quotes(input, &i, input[i]) == ERROR)
				return (ERROR);
			continue ;
		}
		if (input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '\0'))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Validates the use of redirects in the input string.
 *
 * This function checks the input string for invalid use of redirects, such as
 * having consecutive redirects or having a redirect at the end of the string.
 *
 * @param input The input string to be validated.
 * @return SUCCESS if the input string is valid, or an error status otherwise.
 */
static t_status	ft_validate_redirects(char *input)
{
	int	i;
	int	operator_len;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (ft_skip_quotes(input, &i, input[i]) == ERROR)
				return (ERROR);
			continue ;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
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
				return (ERROR);
			}
		}
		else
			i++;
	}
	return (SUCCESS);
}

/**
 * @brief Validates the syntax of a given input string.
 *
 * This function validates the syntax of the given input string by checking for
 * invalid use of quotes, consecutive pipes, and invalid use of redirects.
 *
 * @param input The input string to be validated.
 * @return SUCCESS if the input string is valid, or an error status otherwise.
 */
t_status	ft_validate_syntax(char *input)
{
	char	*input_cpy;

	input_cpy = ft_strdup(input);
	if (!input_cpy)
		return (ft_print_error(ERR_MALLOC_FAIL));
	ft_remove_spaces(input_cpy);
	if (ft_strlen(input_cpy) == 0)
		return (ft_free(input_cpy), ERROR);
	if (ft_check_quotes(input_cpy) != SUCCESS)
		return (ft_free(input_cpy), ft_print_unmatched_quote_error());
	if (ft_validate_pipes(input_cpy) != SUCCESS)
		return (ft_free(input_cpy), ft_print_syntax_error("|"));
	if (ft_validate_redirects(input_cpy) != SUCCESS)
		return (ft_free(input_cpy), ERROR);
	ft_free(input_cpy);
	return (SUCCESS);
}
