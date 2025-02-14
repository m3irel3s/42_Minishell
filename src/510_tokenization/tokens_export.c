/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:19:26 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/14 17:29:06 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		ft_update_quote_count(int quote_count, char quote_char, char c);
static char		ft_update_quote_char(char quote_char, char c);
static int		ft_count_unmatched_quotes(t_shell *shell, size_t *i);
static t_status	ft_handle_export_token_quotes(t_shell *shell, size_t *i);

/**
 * @brief Handles the tokenization of a word token with the export command.
 *
 * This function is called when a word token is encountered in the input string.
 * It handles the tokenization of the word token and checks if there are any
 * unmatched single or double quotes in the token. If there are, it sets the
 * status to ERROR and returns. If not, it creates a new token with the
 * appropriate value and type, and adds it to the shell's token list.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and the token list.
 * @param i A pointer to the index of the current character in the input string.
 *
 * @return Returns SUCCESS if the token is successfully created and added to
 *         the token list; otherwise, returns ERROR.
 */
t_status	ft_handle_export_token(t_shell *shell, size_t *i)
{
	size_t start;

	start = *i;
	if (ft_handle_export_token_quotes(shell, i) != SUCCESS)
		return (ERROR);
	return (ft_create_and_add_token(shell, start, *i, 0));
}

static t_status	ft_handle_export_token_quotes(t_shell *shell, size_t *i)
{
	int quote_count;

	quote_count = ft_count_unmatched_quotes(shell, i);
	if (quote_count != 0)
	{
		ft_putstr_fd("minishell: syntax error: unmatched quote\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	ft_count_unmatched_quotes(t_shell *shell, size_t *i)
{
	int quote_count;
	char quote_char;
	size_t original_i;

	quote_count = 0;
	quote_char = 0;
	original_i = *i;
	while (shell->input[*i] && !ft_is_space(shell->input[*i]) && !ft_is_operator(shell->input[*i]))
		(*i)++;
	*i = original_i;
	while (shell->input[*i] && !ft_is_space(shell->input[*i]) && !ft_is_operator(shell->input[*i]))
	{
		if (shell->input[*i] == '\'' || shell->input[*i] == '"')
		{
			quote_count = ft_update_quote_count(quote_count, quote_char, shell->input[*i]);
			quote_char = ft_update_quote_char(quote_char, shell->input[*i]);
		}
		(*i)++;
	}
	return (quote_count);
}

static int ft_update_quote_count(int quote_count, char quote_char, char c)
{
	if (quote_char == 0)
	{
		quote_char = c;
		quote_count++;
	}
	else if (c == quote_char)
	{
		quote_char = 0;
		quote_count--;
	}
	else
	{
		quote_char = c;
		quote_count++;
	}
	return (quote_count);
}

static char ft_update_quote_char(char quote_char, char c)
{
	if (quote_char == 0)
		return (c);
	else if (c == quote_char)
		return (0);
	else
		return (c);
}
