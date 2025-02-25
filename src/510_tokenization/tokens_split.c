/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/25 10:28:28 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_word(char *input, size_t *i, char **result,
			size_t *k);
static void		ft_split_word(char *input, size_t *i, int *in_quotes,
			char *q_char);
static char		**ft_alloc_result(char *input);
static t_status	ft_add_token(char **result, char *input, size_t j, size_t i);

/**
 * @brief Splits the input string into an array of strings (words).
 *
 * This function splits the input string into an array of strings, respecting
 * quotes to ensure that quoted substrings are not split. It handles both
 * single and double quotes.
 *
 * @param input The input string to be split.
 * @return An array of strings (words) or NULL if memory allocation fails.
 */
char	**ft_split_input(char *input)
{
	char	**result;
	size_t	i;
	size_t	k;

	if (!input)
		return (NULL);
	result = ft_alloc_result(input);
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (ft_process_word(input, &i, result, &k) != SUCCESS)
			return (NULL);
	}
	result[k] = NULL;
	return (result);
}

/**
 * @brief Processes a single word in the input string.
 *
 * This function handles the processing of a single word, including
 * quote handling and token creation.
 *
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param result The array to store the resulting tokens.
 * @param k Pointer to the current index in the result array.
 * @return SUCCESS if processing succeeds, ERROR otherwise.
 */
static t_status	ft_process_word(char *input, size_t *i, char **result,
	size_t *k)
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
 * @brief Splits a single word from the input string.
 *
 * This function processes a single word in the input string, handling quoted
 * sections and updating the current position accordingly.
 *
 * @param input The input string being processed.
 * @param i Pointer to the current index in the input string.
 * @param in_quotes Pointer to the flag indicating if currently in quotes.
 * @param q_char Pointer to store the current quote character.
 */
static void	ft_split_word(char *input, size_t *i, int *in_quotes, char *q_char)
{
	while (input[*i] && (*in_quotes || !ft_is_space(input[*i])))
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
 * @brief Allocates memory for the result array.
 *
 * This function allocates memory for an array of strings to hold the split
 * input. The size of the array is determined by the number of words in the
 * input string plus one for the NULL terminator.
 *
 * @param input The input string to be split.
 * @return A pointer to the allocated array or NULL if allocation fails.
 */
static char	**ft_alloc_result(char *input)
{
	char	**result;
	int		word_count;

	word_count = ft_count_words(input);
	if (word_count < 0)
	{
		ft_print_error(ERR_WORD_COUNT_FAIL);
		return (NULL);
	}
	result = ft_safe_malloc(sizeof(char *) * (word_count + 1));
	if (!result)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		return (NULL);
	}
	return (result);
}

/**
 * @brief Adds a token to the result array.
 *
 * This function creates a substring from the input string and adds it as a
 * token to the result array. If memory allocation fails, it frees the result
 * array and returns an error.
 *
 * @param result The result array to add the token to.
 * @param input The input string to extract the token from.
 * @param j The start index of the token in the input string.
 * @param i The end index of the token in the input string.
 * @return SUCCESS if the token is added successfully, ERROR otherwise.
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
