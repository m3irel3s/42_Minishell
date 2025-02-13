/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/12 22:29:00 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status	ft_handle_quote(t_shell *shell, size_t *i, int *quoted_status);
static t_status	ft_handle_operator(t_shell *shell, size_t *i,
					int quoted_status);

/**
 * @brief Tokenizes the shell's input string into a linked list of tokens.
 *
 * This function checks if the shell structure and its input string are valid.
 * If so, it calls ft_process_and_tokenize to tokenize the input string.
 * If either the shell or its input is invalid, the function returns ERROR.
 * Otherwise, it returns the result of ft_process_and_tokenize.
 *
 * @param shell A pointer to the shell structure containing the input string.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
 */
int	ft_tokenize(t_shell *shell)
{
	if (!shell || !shell->input)
		return (ERROR);
	return (ft_process_and_tokenize(shell));
}

/**
 * @brief Tokenizes the shell input by processing quoted strings, operators,
 * and words.
 *
 * This function iterates through the shell's input string and processes each
 * character. It handles quoted strings by calling ft_handle_quote,
 * operators by calling ft_handle_operator, and words by calling ft_handle_word.
 * Quoted status is tracked so that quoted strings can be processed correctly.
 * If any of the helper functions return ERROR, this function also returns ERROR.
 * Otherwise, it returns SUCCESS after processing the entire input string.
 *
 * @param shell A pointer to the shell structure containing the input string.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
 */
static t_status	ft_process_and_tokenize(t_shell *shell)
{
	size_t	i;
	int		quoted_status;

	i = 0;
	quoted_status = 0;
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
			i++;
		else if (ft_is_quote(shell->input[i]))
		{
			if (ft_handle_quote(shell, &i, &quoted_status) == ERROR)
				return (ERROR);
		}
		else if (ft_is_operator(shell->input[i]))
		{
			if (ft_handle_operator(shell, &i, quoted_status) == ERROR)
				return (ERROR);
		}
		else if (ft_handle_word(shell, &i, &quoted_status) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static t_status ft_handle_quote(t_shell *shell, size_t *i, int *quoted_status)
{
	size_t start;
	char quote_char;
	t_status status;
	t_token *last_token;
	char *word;

	quote_char = shell->input[*i];
	if (quote_char == '\'')
		*quoted_status = 1;
	else
		*quoted_status = 2;
	start = *i + 1;
	(*i)++;
	while (shell->input[*i] && shell->input[*i] != quote_char)
		(*i)++;
	if (!shell->input[*i])
	{
		ft_putstr_fd("minishell: error: unmatched quote\n", STDERR_FILENO);
		return (ERROR);
	}
	if (ft_create_and_add_token(shell, start, *i, *quoted_status) == ERROR)
		return (ERROR);
	(*i)++;
	*quoted_status = 0;
	if (shell->in_export)
	{
		last_token = shell->tokens;
		while (last_token && last_token->next)
			last_token = last_token->next;
		if (last_token && last_token->quoted)
		{
			word = ft_strdup(last_token->value);
			if (!word)
				return (ERROR);
			status = ft_process_export_assignment(shell, word);
			free(word);
			if (status != SUCCESS)
				return (status);
			if (last_token->prev)
				last_token->prev->next = NULL;
			else
				shell->tokens = NULL;
			free(last_token->value);
			free(last_token);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Processes an operator token in the shell input and adds it to the token
 * list.
 *
 * This function identifies an operator in the shell's input starting from the
 * current index and continues until a non-operator character is encountered. It
 * then creates and adds a new token representing the operator to the shell's
 * token list. The function takes into account whether the operator is quoted.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will be
 *          updated to the index after the processed operator.
 * @param quoted_status An integer indicating the quoted status of the operator.
 *
 * @return Returns SUCCESS if the operator token is successfully created and
 *         added;
 *         otherwise, returns ERROR.
 */
static t_status	ft_handle_operator(t_shell *shell, size_t *i, int quoted_status)
{
	size_t	start;
	char	*op_str;

	start = *i;
	while (ft_is_operator(shell->input[*i]))
		(*i)++;
	op_str = ft_substr(shell->input, start, *i - start);
	if (ft_strcmp(op_str, "|") == 0)
		shell->in_export = 0;
	free(op_str);
	if (ft_create_and_add_token(shell, start, *i, quoted_status) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
