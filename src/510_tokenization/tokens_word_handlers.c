/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_word_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 09:13:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_status	ft_handle_non_operator(t_shell *shell, size_t *i, int *is_export)
{
	if (ft_is_export_command(shell, *i))
	{
		if (ft_create_export_token(shell, i, is_export) != SUCCESS)
			return (ERROR);
		*is_export = 1;
	}
	else
	{
		if (*is_export)
		{
			if (ft_handle_export_arg(shell, i) != SUCCESS)
				return (ERROR);
			*is_export = 0;
		}
		else if (ft_process_word(shell, i) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

t_status	ft_process_word(t_shell *shell, size_t *i)
{
	size_t	start;
	int		in_quotes;
	char	quote_char;

	start = *i;
	in_quotes = 0;
	quote_char = 0;
	while (shell->input[*i] && ((!ft_is_space(shell->input[*i])
			&& !ft_is_operator(shell->input[*i])) || in_quotes))
	{
		ft_update_quote_state(shell->input[*i], &in_quotes, &quote_char);
		(*i)++;
	}
	if (in_quotes)
		return (ft_print_unmatched_quote_error());
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

void	ft_update_quote_state(char c, int *in_quotes, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = c;
		}
		else if (c == *quote_char)
		{
			*in_quotes = 0;
			*quote_char = 0;
		}
	}
}
