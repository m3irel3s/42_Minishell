/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 14:03:31 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
					size_t *start, t_quote_info *quote_info);
static t_status	ft_handle_quote(t_shell *shell, size_t *i, size_t *start,
					t_quote_info *quote_info);
static void		ft_reset_quote_info(t_quote_info *quote_info);

t_status	ft_handle_word(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;

	start = *i;
	ft_reset_quote_info(&quote_info);
	if (ft_process_quoted_word(shell, i, &start, &quote_info) != SUCCESS)
		return (ERROR);
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i,
				quote_info.quoted) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

static t_status	ft_process_quoted_word(t_shell *shell, size_t *i,
		size_t *start, t_quote_info *quote_info)
{
	while (shell->input[*i] && ((!ft_is_space(shell->input[*i])
				&& !ft_is_operator(shell->input[*i])) || quote_info->in_quotes))
	{
		if (ft_handle_quote(shell, i, start, quote_info) != SUCCESS)
			return (ERROR);
		(*i)++;
	}
	if (quote_info->in_quotes)
		return (ft_print_unmatched_quote_error());
	return (SUCCESS);
}

static t_status	ft_handle_quote(t_shell *shell, size_t *i,
			size_t *start, t_quote_info *quote_info)
{
	if (shell->input[*i] == '\'' || shell->input[*i] == '"')
	{
		if (!quote_info->in_quotes)
		{
			if (*i > *start)
			{
				if (ft_create_and_add_token(shell, *start, *i,
						quote_info->quoted) != SUCCESS)
					return (ERROR);
			}
			quote_info->in_quotes = 1;
			quote_info->quote_char = shell->input[*i];
			quote_info->quoted = 2 - (shell->input[*i] == '\'');
			*start = *i + 1;
		}
		else if (shell->input[*i] == quote_info->quote_char)
		{
			if (ft_create_and_add_token(shell, *start, *i,
					quote_info->quoted) != SUCCESS)
				return (ERROR);
			ft_reset_quote_info(quote_info);
			*start = *i + 1;
		}
	}
	return (SUCCESS);
}

static void	ft_reset_quote_info(t_quote_info *quote_info)
{
	quote_info->in_quotes = 0;
	quote_info->quote_char = 0;
	quote_info->quoted = 0;
}
