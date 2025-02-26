/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/26 10:07:08 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h> // For debug statements

static t_status ft_process_word(char *input, size_t *i, char **result, size_t *k);
static void ft_split_word(char *input, size_t *i, int *in_quotes, char *q_char);
static char **ft_alloc_result(char *input);
static t_status ft_add_token(char **result, char *input, size_t j, size_t i);

char **ft_split_input(char *input)
{
	printf("[DEBUG] Entering ft_split_input with input: '%s'\n", input);
	char **result;
	size_t i = 0;
	size_t k = 0;

	if (!input)
		return (NULL);
	result = ft_alloc_result(input);
	if (!result)
		return (NULL);

	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			break;

		printf("[DEBUG] Processing input at index %zu: '%c'\n", i, input[i]);

		if (ft_is_operator(input[i]))
		{
			printf("[DEBUG] Found operator at index %zu\n", i);
			size_t start = i;
			if (ft_is_double_operator(&input[i]))
				i += 2;
			else
				i++;

			if (ft_add_token(&result[k++], input, start, i) != SUCCESS)
			{
				printf("[ERROR] Failed to add operator token.\n");
				ft_free_arr(result);
				return (NULL);
			}
			continue;
		}

		if (ft_process_word(input, &i, result, &k) != SUCCESS)
		{
			printf("[ERROR] Failed to process word at index %zu.\n", i);
			ft_free_arr(result);
			return (NULL);
		}
	}
	result[k] = NULL;
	printf("[DEBUG] Exiting ft_split_input with %zu tokens.\n", k);
	return (result);
}

static t_status ft_process_word(char *input, size_t *i, char **result, size_t *k)
{
	printf("[DEBUG] Entering ft_process_word at index %zu\n", *i);
	size_t j = *i;
	int in_quotes = 0;
	char quote_char;

	ft_split_word(input, i, &in_quotes, &quote_char);
	printf("[DEBUG] Processed word from index %zu to %zu\n", j, *i);

	if (ft_add_token(&result[(*k)++], input, j, *i) != SUCCESS)
	{
		printf("[ERROR] Token creation failed for substring [%zu:%zu].\n", j, *i);
		ft_print_error(ERR_TOKEN_CREATION_FAIL);
		return (ERROR);
	}
	return (SUCCESS);
}

static void ft_split_word(char *input, size_t *i, int *in_quotes, char *q_char)
{
	printf("[DEBUG] Entering ft_split_word at index %zu\n", *i);
	while (input[*i] && (*in_quotes || (!ft_is_space(input[*i]) && !ft_is_operator(input[*i]))))
	{
		if ((input[*i] == '\'' || input[*i] == '"') && !*in_quotes)
		{
			*in_quotes = 1;
			*q_char = input[*i];
			printf("[DEBUG] Entering quotes with char '%c' at index %zu\n", *q_char, *i);
		}
		else if (*in_quotes && input[*i] == *q_char)
		{
			*in_quotes = 0;
			printf("[DEBUG] Exiting quotes with char '%c' at index %zu\n", *q_char, *i);
		}
		(*i)++;
	}
	printf("[DEBUG] Exiting ft_split_word at index %zu\n", *i);
}

static char **ft_alloc_result(char *input)
{
	printf("[DEBUG] Allocating result array for input: '%s'\n", input);
	char **result;
	int word_count = ft_count_words(input);

	if (word_count < 0)
	{
		printf("[ERROR] Word count failed.\n");
		ft_print_error(ERR_WORD_COUNT_FAIL);
		return (NULL);
	}
	result = ft_safe_malloc(sizeof(char *) * (word_count + 1));
	if (!result)
	{
		printf("[ERROR] Memory allocation failed for result array.\n");
		ft_print_error(ERR_MALLOC_FAIL);
		return (NULL);
	}
	printf("[DEBUG] Successfully allocated memory for %d words.\n", word_count);
	return (result);
}

static t_status ft_add_token(char **result, char *input, size_t j, size_t i)
{
	printf("[DEBUG] Adding token from index %zu to %zu\n", j, i);
	char *token = ft_safe_substr(input, j, i - j);

	if (!token)
	{
		printf("[ERROR] Substring creation failed for token [%zu:%zu].\n", j, i);
		ft_free_arr(result);
		ft_print_error(ERR_SUBSTR_FAIL);
		return (ERROR);
	}
	printf("[DEBUG] Successfully added token: '%s'\n", token);
	*result = token;
	return (SUCCESS);
}
