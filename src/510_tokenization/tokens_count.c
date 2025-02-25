/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/24 21:47:24 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_count_word(char *input, size_t *i, int *in_quotes);

/**
 * @brief Counts the number of words in the input string.
 *
 * This function counts the number of words in the input string, respecting
 * quotes to ensure that quoted substrings are not counted as separate words.
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
	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		count++;
		while (input[i] && (in_quotes || !ft_is_space(input[i])))
			ft_count_word(input, &i, &in_quotes);
	}
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
	if ((input[*i] == '\'' || input[*i] == '\"') && !*in_quotes)
	{
		*in_quotes = 1;
		quote_char = input[*i];
	}
	else if (*in_quotes && input[*i] == quote_char)
		*in_quotes = 0;
	(*i)++;
}
