/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/14 17:29:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status ft_handle_operator(t_shell *shell, size_t *i, int *is_export);
static t_status ft_handle_word_token(t_shell *shell, size_t *i, int *is_export);
static t_status ft_process_word_token(t_shell *shell, size_t *i);

int ft_tokenize(t_shell *shell)
{
	size_t i;
	int is_export;

	i = 0;
	is_export = 0;
	if (!shell || !shell->input)
		return (ERROR);
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
			i++;
		else if (ft_is_operator(shell->input[i]))
		{
			if (ft_handle_operator(shell, &i, &is_export) != SUCCESS)
				return (ERROR);
		}
		else
		{
			if (ft_handle_word_token(shell, &i, &is_export) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

static t_status ft_handle_operator(t_shell *shell, size_t *i, int *is_export)
{
	size_t start;

	start = *i;
	if (*is_export)
		*is_export = 0;
	if (ft_is_double_operator(shell->input + *i))
		*i += 2;
	else
		(*i)++;
	return (ft_create_and_add_token(shell, start, *i, 0));
}

static t_status ft_handle_word_token(t_shell *shell, size_t *i, int *is_export)
{
	size_t start;

	start = *i;
	if (ft_strncmp(shell->input + *i, "export", 6) == 0)
	{
		if (ft_is_space(shell->input[*i + 6]) || shell->input[*i + 6] == '\0')
		{
			*is_export = 1;
			*i += 6;
			return (ft_create_and_add_token(shell, start, *i, 0));
		}
	}
	if (*is_export)
		return (ft_handle_export_token(shell, i));
	else
		return (ft_process_word_token(shell, i));
}

static t_status ft_process_word_token(t_shell *shell, size_t *i)
{
	size_t start = *i;
	int in_quotes = 0;
	char quote_char = 0;

	while (shell->input[*i] && !ft_is_space(shell->input[*i]) && !ft_is_operator(shell->input[*i]))
	{
		if (shell->input[*i] == '\'' || shell->input[*i] == '"')
		{
			if (!in_quotes)
			{
				if (*i > start)
				{
					if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
						return (ERROR);
				}
				in_quotes = 1;
				quote_char = shell->input[*i];
				start = *i + 1;
			}
			else if (shell->input[*i] == quote_char)
			{
				if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
					return (ERROR);
				in_quotes = 0;
				quote_char = 0;
				start = *i + 1;
			}
		}
		(*i)++;
	}
	if (in_quotes)
	{
		ft_putstr_fd("minishell: syntax error: unmatched quote\n", 2);
		return (ERROR);
	}
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
