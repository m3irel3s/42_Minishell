/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 14:20:31 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char		**ft_alloc_result(char *input);

/**
 * @brief Splits the input string into tokens and stores them in the result
 * array.
 *
 * This function allocates memory for the result array and calls the
 * ft_build_tokens function to process the input string and store the tokens in
 * the result array.
 *
 * @param input The input string.
 * @return A pointer to the array of tokens or NULL if there is a memory
 * allocation failure or unmatched quotes.
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
	if (ft_build_tokens(input, result, &i, &k) != SUCCESS)
	{
		ft_print_error(ERR_TOKEN_CREATION_FAIL);
		ft_free_arr(result);
		return (NULL);
	}
	result[k] = NULL;
	return (result);
}

/**
 * @brief Splits the input string into tokens and stores them in the result
 * array.
 *
 * This function iterates over the input string, skipping whitespace characters
 * and processing operators and words. Operators are handled by the
 * ft_handle_t_operator function, and words are handled by the ft_process_word
 * function.
 *
 * @param input The input string.
 * @param result The array of tokens where the processed tokens will be stored.
 * @param i The index of the current character in the input string.
 * @param k The index of the current token in the result array.
 * @return SUCCESS if the input is processed successfully, or an error status if
 * there is a memory allocation failure or unmatched quotes.
 */
int	ft_build_tokens(char *input, char **result, size_t *i, size_t *k)
{
	while (input[*i])
	{
		while (input[*i] && ft_is_space(input[*i]))
			*i += 1;
		if (!input[*i])
			break ;
		if (ft_is_operator(input[*i]))
		{
			if (ft_handle_t_operator(input, i, result, k) != SUCCESS)
			{
				ft_print_error(ERR_TOKENIZATION_FAIL);
				return (ERROR);
			}
			continue ;
		}
		if (ft_process_word(input, i, result, k) != SUCCESS)
		{
			ft_print_error(ERR_TOKENIZATION_FAIL);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Allocates memory for the result array.
 *
 * This function allocates memory for the result array and returns a pointer to
 * the first element of the array.
 *
 * @param input The input string.
 * @return A pointer to the first element of the result array or NULL if there
 * is a memory allocation failure.
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
	result = ft_safe_calloc(sizeof(char *) * (word_count + 1));
	if (!result)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		return (NULL);
	}
	return (result);
}
