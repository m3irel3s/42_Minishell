/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:04:16 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/06 16:30:36 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char		**ft_alloc_result(char *input);

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
		ft_free_arr(result);
		return (NULL);
	}
	result[k] = NULL;
	return (result);
}

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
				return (ERROR);
			continue ;
		}
		if (ft_process_word(input, i, result, k) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

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
