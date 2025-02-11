/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 16:09:09 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status	ft_handle_quote(t_shell *shell, size_t *i, int *quoted_status);
static t_status	ft_handle_operator(t_shell *shell, size_t *i,
					int quoted_status);
static t_status	ft_handle_word(t_shell *shell, size_t *i, int quoted_status);

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
		else if (ft_handle_word(shell, &i, quoted_status) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Processes a quoted string in the shell input and adds it as a token to
 * the token list.
 *
 * This function identifies a quoted string in the shell's input starting from
 * the current index. It continues until the matching quote character is
 * encountered or an unmatched quote error is detected. The function then creates
 * and adds a new token representing the quoted string to the shell's token list.
 * It updates the quoted status based on the type of quote encountered (single
 * or double).
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will be
 *          updated to the index after the processed quoted string.
 * @param quoted_status A pointer to an integer that indicates the quoted status
 *                      of the string (1 for single quote, 2 for double quote).
 *
 * @return Returns SUCCESS if the quoted string token is successfully created
 *         and added; otherwise, returns ERROR if unmatched quote is detected.
 */

static t_status	ft_handle_quote(t_shell *shell, size_t *i, int *quoted_status)
{
	size_t	start;
	char	quote_char;

	quote_char = shell->input[*i];
	*quoted_status = (quote_char == '\'') + (quote_char == '"') * 2;
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

	start = *i;
	while (ft_is_operator(shell->input[*i]))
		(*i)++;
	if (ft_create_and_add_token(shell, start, *i, quoted_status) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Processes a word token in the shell input and adds it to the token
 * list.
 *
 * This function identifies a word in the shell's input starting from the
 * current index and continues until a non-word character is encountered. It then
 * creates and adds a new token representing the word to the shell's token list.
 * The function takes into account whether the word is quoted.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will be
 *          updated to the index after the processed word.
 * @param quoted_status An integer indicating the quoted status of the word.
 *
 * @return Returns SUCCESS if the word token is successfully created and added;
 *         otherwise, returns ERROR.
 */
static t_status	ft_handle_word(t_shell *shell, size_t *i, int quoted_status)
{
	size_t	start;

	start = *i;
	while (shell->input[*i] && !ft_is_space(shell->input[*i])
		&& !ft_is_operator(shell->input[*i]) && !ft_is_quote(shell->input[*i]))
		(*i)++;
	if (ft_create_and_add_token(shell, start, *i, quoted_status) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
