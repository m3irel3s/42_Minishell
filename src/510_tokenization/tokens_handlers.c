/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 10:27:50 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
				t_quote_info *quote_info);

t_status	ft_handle_operator(t_shell *shell, size_t *i, int *is_export)
{
	size_t	start;

	if (*is_export)
		*is_export = 0;
	start = *i;
	if (ft_is_double_operator(shell->input + *i))
		*i += 2;
	else
		(*i)++;
	return (ft_create_and_add_token(shell, start, *i, 0));
}

t_status	ft_handle_export_arg(t_shell *shell, size_t *i)
{
	size_t			start;
	t_quote_info	quote_info;

	start = *i;
	quote_info.in_quotes = 0;
	quote_info.quote_char = 0;
	ft_set_export_arg_index(shell, i, &quote_info);
	if (quote_info.in_quotes != 0)
		return (ft_print_unmatched_quote_error());
	while (*i > start && ft_is_space(shell->input[*i - 1]))
		(*i)--;
	return (ft_create_and_add_token(shell, start, *i, 0));
}

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
		t_quote_info *quote_info)
{
	while (shell->input[*i])
	{
		if (shell->input[*i] == '\'' || shell->input[*i] == '"')
		{
			if (!quote_info->quote_char)
			{
				quote_info->quote_char = shell->input[*i];
				quote_info->in_quotes++;
			}
			else if (shell->input[*i] == quote_info->quote_char)
			{
				quote_info->in_quotes--;
				if (quote_info->in_quotes == 0)
					quote_info->quote_char = 0;
			}
		}
		else if (!quote_info->in_quotes && (ft_is_space(shell->input[*i])
				|| ft_is_operator(shell->input[*i])))
			break ;
		(*i)++;
	}
}
