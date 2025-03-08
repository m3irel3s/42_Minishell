/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:19:19 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 15:24:44 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_split_word(char *input, size_t *i, \
					int *in_quotes, char *q_char);
static t_status	ft_add_token(char **result, char *input, size_t j, size_t i);

/**
 * @brief Handles operators in the input string.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param result The array of tokens where the operator will be added.
 * @param k Pointer to the index of the token in the result array.
 * @return SUCCESS if the operator was added successfully, ERROR otherwise.
 */
int	ft_handle_t_operator(char *input, size_t *i, char **result, size_t *k)
{
	size_t	start;

	start = *i;
	if (ft_is_double_operator(&input[*i]))
		*i += 2;
	else
		*i += 1;
	if (ft_add_token(&result[*k], input, start, *i) != SUCCESS)
	{
		ft_print_error(ERR_TOKEN_CREATION_FAIL);
		ft_free_arr(result);
		return (ERROR);
	}
	*k += 1;
	return (SUCCESS);
}

/**
 * @brief Processes a single word in the input string.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param result The array of tokens where the word will be added.
 * @param k Pointer to the index of the token in the result array.
 * @return SUCCESS if the word was added successfully, ERROR otherwise.
 */
t_status	ft_process_word(char *input, size_t *i, char **result, size_t *k)
{
	size_t	j;
	int		in_quotes;
	char	quote_char;

	j = *i;
	in_quotes = 0;
	ft_split_word(input, i, &in_quotes, &quote_char);
	if (ft_add_token(&result[(*k)++], input, j, *i) != SUCCESS)
	{
		ft_print_error(ERR_TOKEN_CREATION_FAIL);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Splits a word in the input string, considering quotes and
 * operators.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param in_quotes Pointer to the flag indicating if currently in quotes.
 * @param q_char Pointer to the current quote character.
 */
static void	ft_split_word(char *input, size_t *i, int *in_quotes, char *q_char)
{
	while (input[*i] && (*in_quotes || (!ft_is_space(input[*i])
				&& !ft_is_operator(input[*i]))))
	{
		if ((input[*i] == '\'' || input[*i] == '\"') && !*in_quotes)
		{
			*in_quotes = 1;
			*q_char = input[*i];
		}
		else if (*in_quotes && input[*i] == *q_char)
			*in_quotes = 0;
		(*i)++;
	}
}

/**
 * @brief Creates a new token by creating a substring of the input string
 * and assigns it to the result pointer.
 * @param result The pointer where the new token will be assigned.
 * @param input The input string.
 * @param j The start index of the new token.
 * @param i The end index of the new token.
 * @return SUCCESS if the new token was created successfully, ERROR otherwise.
 */
static t_status	ft_add_token(char **result, char *input, size_t j, size_t i)
{
	char	*token;

	token = ft_safe_substr(input, j, i - j);
	if (!token)
	{
		ft_free_arr(result);
		ft_print_error(ERR_SUBSTR_FAIL);
		return (ERROR);
	}
	*result = token;
	return (SUCCESS);
}
