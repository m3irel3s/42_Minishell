/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 10:00:30 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
				int *quote_count, char *quote_char);

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
	size_t	start;
	int		quote_count;
	char	quote_char;

	start = *i;
	quote_count = 0;
	quote_char = 0;
	ft_set_export_arg_index(shell, i, &quote_count, &quote_char);
	if (quote_count != 0)
		return (ft_print_unmatched_quote_error());
	while (*i > start && ft_is_space(shell->input[*i - 1]))
		(*i)--;
	return (ft_create_and_add_token(shell, start, *i, 0));
}

static void	ft_set_export_arg_index(t_shell *shell, size_t *i,
		int *quote_count, char *quote_char)
{
	while (shell->input[*i])
	{
		if (shell->input[*i] == '\'' || shell->input[*i] == '"')
		{
			if (!*quote_char)
			{
				*quote_char = shell->input[*i];
				(*quote_count)++;
			}
			else if (shell->input[*i] == *quote_char)
			{
				(*quote_count)--;
				if (*quote_count == 0)
					*quote_char = 0;
			}
		}
		else if (!*quote_count && (ft_is_space(shell->input[*i])
				|| ft_is_operator(shell->input[*i])))
			break ;
		(*i)++;
	}
}
