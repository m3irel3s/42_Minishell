/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 09:10:33 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status ft_process_and_tokenize(t_shell *shell);

t_status	ft_tokenize(t_shell *shell)
{
	if (!shell || !shell->input)
		return (ERROR);
	return (ft_process_and_tokenize(shell));
}

static t_status ft_process_word_token(t_shell *shell, size_t *i)
{
	size_t start = *i;
	int in_quotes = 0;
	char quote_char = 0;

	while (shell->input[*i] && ( (!ft_is_space(shell->input[*i]) && !ft_is_operator(shell->input[*i])) || in_quotes ))
{
		if (shell->input[*i] == '\'' || shell->input[*i] == '"')
		{
			if (!in_quotes)
			{
				if (*i > start)
				{
					if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
						return ERROR;
				}
				in_quotes = 1;
				quote_char = shell->input[*i];
				start = *i + 1;
			}
			else if (shell->input[*i] == quote_char)
			{
				if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
					return ERROR;
				in_quotes = 0;
				quote_char = 0;
				start = *i + 1;
			}
		}
		(*i)++;
	}
	if (in_quotes)
		return (ft_print_unmatched_quote_error());
	if (*i > start)
	{
		if (ft_create_and_add_token(shell, start, *i, 0) != SUCCESS)
			return ERROR;
	}

	return SUCCESS;
}

static t_status ft_process_and_tokenize(t_shell *shell)
{
	size_t i = 0;
	int is_export = 0;

	if (!shell || !shell->input)
		return ERROR;

	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
			i++;
		else if (ft_is_operator(shell->input[i]))
		{
			if (ft_handle_operator(shell, &i, &is_export) != SUCCESS)
				return ERROR;
		}
		else
		{
			if (ft_is_export_command(shell, i))
			{
				if (ft_create_export_token(shell, &i, &is_export) != SUCCESS)
					return ERROR;
			}
			else
			{
				if (is_export)
				{
					if (ft_handle_export_arg(shell, &i) != SUCCESS)
						return ERROR;
				}
				else
				{
					if (ft_process_word_token(shell, &i) != SUCCESS)
						return ERROR;
				}
			}
		}
	}
	return SUCCESS;
}
