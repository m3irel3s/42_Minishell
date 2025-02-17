/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 09:55:33 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status ft_process_quoted_word(t_shell *shell, size_t *i, size_t *start, int *in_quotes, char *quote_char);
static t_status ft_handle_quote(t_shell *shell, size_t *i, size_t *start, int *in_quotes, char *quote_char);

t_status	ft_handle_word(t_shell *shell, size_t *i)
{
	size_t	start;
	int		in_quotes;
	char	quote_char;

	start = *i;
	in_quotes = 0;
	quote_char = 0;
	if (ft_process_quoted_word(shell, i, &start, &in_quotes, &quote_char) != SUCCESS)
		return ERROR;
	if (in_quotes)
		return (ft_print_unmatched_quote_error());
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
static t_status ft_process_quoted_word(t_shell *shell, size_t *i, size_t *start, int *in_quotes, char *quote_char)
{
	while (shell->input[*i] && ( (!ft_is_space(shell->input[*i]) && !ft_is_operator(shell->input[*i])) || *in_quotes ))
{
		if (ft_handle_quote(shell, i, start, in_quotes, quote_char) != SUCCESS)
			return (ERROR);
		(*i)++;
	}
	return (SUCCESS);
}

static t_status ft_handle_quote(t_shell *shell, size_t *i, size_t *start, int *in_quotes, char *quote_char)
{
	if (shell->input[*i] == '\'' || shell->input[*i] == '"')
	{
		if (!*in_quotes)
		{
			if (*i > *start)
			{
				if (ft_create_and_add_token(shell, *start, *i, 0) != SUCCESS)
					return (ERROR);
			}
			*in_quotes = 1;
			*quote_char = shell->input[*i];
			*start = *i + 1;
		}
		else if (shell->input[*i] == *quote_char)
		{
			if (ft_create_and_add_token(shell, *start, *i, 0) != SUCCESS)
				return (ERROR);
			*in_quotes = 0;
			*quote_char = 0;
			*start = *i + 1;
		}
	}
	return (SUCCESS);
}
