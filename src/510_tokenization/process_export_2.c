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

static t_status	ft_handle_quote_export(t_shell *shell, size_t *i,
					int *quoted_status, char *var_value);
static t_status ft_create_value_token(t_shell *shell, char *var_value,
				size_t *i);
static t_status ft_handle_value_token(t_shell *shell, char *var_value,
				int *quoted_status, size_t *i);

/*************  ✨ Codeium Command ⭐  *************/
/**
 * @brief Processes the value portion of an export command, handling quotes
 * and creating tokens for each part of the value.
 *
 * Iterates over the variable value string, processing each character and
 * handling quoted sections. It creates tokens for unquoted parts and
 * manages the quoted status for quoted parts. Frees the variable value
 * string upon completion.
 *
 * @param shell A pointer to the shell structure.
 * @param var_value The value of the variable to be processed.
 *

 * @return Returns SUCCESS if the value is processed and tokenized
 * correctly, ERROR otherwise.
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
		status = ft_handle_value_token(shell, var_value, &quoted_status, &i);
		if (status == ERROR)
			break;
	}
	free(var_value);
	return (status);
}

/**
 * @brief Processes an unquoted part of an export value string, creating a token.
 *
 * Iterates over the variable value string, processing each character until
 * a quote is found. Creates a token for the unquoted part and frees the
 * substring. If memory allocation fails, it frees the substring and
 * returns ERROR.
 *
 * @param shell A pointer to the shell structure.
 * @param var_value The value of the variable to be processed.
 * @param i A pointer to the current index in the input string.
 *
 * @return Returns SUCCESS if the unquoted part is processed and tokenized
 * correctly, ERROR otherwise.
 */
static t_status	ft_create_value_token(t_shell *shell, char *var_value,
					size_t *i)
{
	size_t	start;
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
 * @brief Handles a segment of the export value string, determining if it is
 * quoted or unquoted, and processes it accordingly.
 *
 * This function checks the current character in the export value string to
 * determine if it is a quote. If it is, it calls ft_handle_quote_export to
 * process the quoted segment. If it is not a quote, it calls
 * ft_create_value_token to process the unquoted segment. It updates the
 * quoted status and the index as needed.
 *
 * @param shell A pointer to the shell structure.
 * @param var_value The value of the variable to be processed.
 * @param quoted_status A pointer to an integer indicating the quoted status.
 * @param i A pointer to the current index in the input string.
 *
 * @return Returns SUCCESS if the segment is processed successfully,
 *         otherwise returns ERROR.
 */

static t_status ft_handle_value_token(t_shell *shell, char *var_value,
				int *quoted_status, size_t *i)
{
	t_status	status;

	status = SUCCESS;
	if (ft_is_quote(var_value[*i]))
	{
		status = ft_handle_quote_export(shell, i, quoted_status, var_value);
	}
	else
	{
		status = ft_create_value_token(shell, var_value, i);
	}
	return (status);
}

/**
 * @brief Processes a quoted segment of the export value string and adds it as
 * a token to the token list.
 *
 * This function identifies a quoted segment of the export value string
 * starting from the current index, and continues until the matching quote
 * character is encountered or an unmatched quote error is detected. It
 * creates and adds a new token representing the quoted segment to the
 * shell's token list. The function takes into account whether the operator
 * is quoted.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will be
 *          updated to the index after the processed quoted segment.
 * @param quoted_status A pointer to an integer indicating the quoted status of
 *                      the string (1 for single quote, 2 for double quote).
 * @param var_value The value of the variable to be processed.
 *
 * @return Returns SUCCESS if the quoted segment is successfully processed and
 *         added; otherwise, returns ERROR if unmatched quote is detected.
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
