/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/26 10:25:57 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h> // For debug statements

static void	ft_count_word(char *input, size_t *i, int *in_quotes);

/**
 * @brief Counts the number of words in the input string.
 *
 * This function counts the number of words in the input string, respecting
 * quotes and treating operators as separate tokens.
 *
 * @param input The input string to be counted.
 * @return The number of words in the input string, or -1 if input is NULL.
 */
int	ft_count_words(char *input)
{
	size_t	i;
	int		count;
	int		in_quotes;

	if (!input)
		return (-1);
	i = 0;
	count = 0;
	in_quotes = 0;
	printf("[DEBUG] Starting ft_count_words with input: '%s'\n", input);
	while (input[i])
	{
		printf("[DEBUG] Processing character '%c' at index %zu\n", input[i], i);
		while (input[i] && ft_is_space(input[i]))
		{
			printf("[DEBUG] Skipping space at index %zu\n", i);
			i++;
		}
		if (!input[i])
			break ;
		if (ft_is_operator(input[i]))
		{
			count++;
			printf("[DEBUG] Found operator '%c' at index %zu (count=%d)\n", input[i], i, count);
			if (ft_is_double_operator(&input[i]))
			{
				printf("[DEBUG] Double operator found at index %zu\n", i);
				i += 2;
			}
			else
				i++;
		}
		else
		{
			count++;
			printf("[DEBUG] Found word start at index %zu (count=%d)\n", i, count);
			while (input[i] && (in_quotes || (!ft_is_space(input[i]) && !ft_is_operator(input[i]))))
			{
				ft_count_word(input, &i, &in_quotes);
				printf("[DEBUG] Word processing at index %zu, in_quotes=%d\n", i, in_quotes);
			}
		}
	}
	printf("[DEBUG] Finished ft_count_words. Total words counted: %d\n", count);
	return (count);
}

/**
 * @brief Counts characters in a word, handling quotes.
 *
 * This function advances the index `i` while considering quoted sections in the
 * input string. It updates the `in_quotes` flag to track if the current position
 * is within quotes, ensuring that quoted substrings are handled correctly.
 *
 * @param input The input string being processed.
 * @param i Pointer to the current index in the input string.
 * @param in_quotes Pointer to the flag indicating if currently in quotes.
 */
static void	ft_count_word(char *input, size_t *i, int *in_quotes)
{
	char	quote_char;

	quote_char = 0;
	printf("[DEBUG] ft_count_word processing character '%c' at index %zu\n", input[*i], *i);
	if ((input[*i] == '\'' || input[*i] == '"') && !*in_quotes)
	{
		*in_quotes = 1;
		quote_char = input[*i];
		printf("[DEBUG] Entering quotes with '%c' at index %zu\n", quote_char, *i);
	}
	else if (*in_quotes && input[*i] == quote_char)
	{
		*in_quotes = 0;
		quote_char = 0;
		printf("[DEBUG] Exiting quotes at index %zu\n", *i);
	}
	(*i)++;
	printf("[DEBUG] Moving to next character at index %zu\n", *i);
}
