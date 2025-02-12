/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:11:58 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/12 22:12:17 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_handle_quote_export(t_shell *shell, size_t *i,
					int *quoted_status, char *var_value);
static t_status ft_create_value_token(t_shell *shell, char *var_value,
				int quoted_status, size_t *i);
static t_status ft_handle_value_token(t_shell *shell, char *var_value,
				int quoted_status, size_t *i);

/**
 * @brief Handles the value part of the export assignment.
 *
 * Processes quotes and adds tokens to the list.
 *
 * @param shell A pointer to the shell structure.
 * @param var_value The value string to be processed.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
t_status	ft_handle_export_value(t_shell *shell, char *var_value)
{
	size_t			i;
	int				quoted_status;
	t_status		status;

	i = 0;
	quoted_status = 0;
	status = SUCCESS;
	while (var_value[i])
	{
		status = ft_handle_value_token(shell, var_value, quoted_status, &i);
		if (status == ERROR)
			break;
	}
	free(var_value);
	return (status);
}

/**
 * @brief create the token and add to the list
 *
 * @param shell A pointer to the shell structure.
 * @param var_value The input string to be processed.
 * @param quoted_status status
 * @param i index
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_create_value_token(t_shell *shell, char *var_value,
					int quoted_status, size_t *i)
{
	size_t	start;
	t_status	status;
	char	*unquoted_part;
	t_token	*token_var_value;

	start = *i;
	while (var_value[*i] && !ft_is_quote(var_value[*i]))
		(*i)++;
	unquoted_part = ft_substr(var_value, start, *i - start);
	if (!unquoted_part)
		return (ERROR);
	token_var_value = ft_create_token(unquoted_part, WORD);
	if (!token_var_value)
	{
		free(unquoted_part);
		return (ERROR);
	}
	free(unquoted_part);
	ft_add_token_to_list(shell, token_var_value);
	return (SUCCESS);
}

/**
 * @brief create the token and add to the list
 *
 * @param shell A pointer to the shell structure.
 * @param var_value The input string to be processed.
 * @param quoted_status status
 * @param i index
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status ft_handle_value_token(t_shell *shell, char *var_value,
					int quoted_status, size_t *i)
{
	t_status	status;

	status = SUCCESS;
	if (ft_is_quote(var_value[*i]))
	{
		status = ft_handle_quote_export(shell, i, &quoted_status, var_value);
	}
	else
	{
		status = ft_create_value_token(shell, var_value, quoted_status, i);
	}
	return (status);
}

/**
 * @brief Handles quotes in export assignments and adds tokens.
 *
 * Extracts quoted part and adds to the token list.
 *
 * @param shell A pointer to the shell structure.
 * @param i A pointer to the current index in var_value.
 * @param quoted_status A pointer to the quoted status.
 * @param var_value The string containing the value.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_handle_quote_export(t_shell *shell, size_t *i,
					int *quoted_status, char *var_value)
{
	size_t	start;
	char	quote_char;
	t_token	*new_token;

	quote_char = var_value[*i];
	*quoted_status = (quote_char == '\'') + (quote_char == '"') * 2;
	start = *i + 1;
	(*i)++;
	while (var_value[*i] && var_value[*i] != quote_char)
		(*i)++;
	if (!var_value[*i])
	{
		ft_putstr_fd("minishell: error: unmatched quote\n", STDERR_FILENO);
		return (ERROR);
	}
	new_token = ft_create_token(ft_substr(var_value, start, *i - start), WORD);
	if (!new_token)
		return (ERROR);
	ft_add_token_to_list(shell, new_token);
	(*i)++;
	*quoted_status = 0;
	return (SUCCESS);
}
