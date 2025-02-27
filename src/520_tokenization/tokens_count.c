/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_skip_spaces(char *input, size_t *i);
static void	ft_handle_operator(char *input, size_t *i, int *count);
static void	ft_handle_quotes(char *input, size_t *i, int *in_quotes, char *q_char);
static void	ft_count_word(char *input, size_t *i, int *in_quotes, char *q_char);

/**
 * @brief Counts the number of words (tokens) in the input string.
 * @param input The input string to be counted.
 * @return The number of words in the input string, or -1 if input is NULL.
 */
int	ft_count_words(char *input)
{
	size_t	i;
	int		count;
	int		in_quotes;
	char	q_char;

	if (!input)
		return (-1);
	i = 0;
	count = 0;
	in_quotes = 0;
	q_char = 0;
	while (input[i])
	{
		ft_skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (ft_is_operator(input[i]))
			ft_handle_operator(input, &i, &count);
		else
		{
			count++;
			ft_count_word(input, &i, &in_quotes, &q_char);
		}
	}
	return (count);
}

/**
 * @brief Skips spaces in the input string.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 */
static void	ft_skip_spaces(char *input, size_t *i)
{
	while (input[*i] && ft_is_space(input[*i]))
		(*i)++;
}

/**
 * @brief Handles operators in the input string.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param count Pointer to the token count.
 */
static void	ft_handle_operator(char *input, size_t *i, int *count)
{
	(*count)++;
	if (ft_is_double_operator(&input[*i]))
		*i += 2;
	else
		(*i)++;
}

/**
 * @brief Handles quotes in the input string.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param in_quotes Pointer to the flag indicating if currently in quotes.
 * @param q_char Pointer to the current quote character.
 */
static void	ft_handle_quotes(char *input, size_t *i, int *in_quotes, char *q_char)
{
	if ((input[*i] == '\'' || input[*i] == '"') && (!*in_quotes || input[*i] == *q_char))
	{
		if (*in_quotes)
		{
			*in_quotes = 0;
			*q_char = 0;
		}
		else
		{
			*in_quotes = 1;
			*q_char = input[*i];
		}
	}
	(*i)++;
}

/**
 * @brief Counts a single word in the input string.
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param in_quotes Pointer to the flag indicating if currently in quotes.
 * @param q_char Pointer to the current quote character.
 */
static void	ft_count_word(char *input, size_t *i, int *in_quotes, char *q_char)
{
	while (input[*i] && (*in_quotes || (!ft_is_space(input[*i]) && !ft_is_operator(input[*i]))))
		ft_handle_quotes(input, i, in_quotes, q_char);
}
