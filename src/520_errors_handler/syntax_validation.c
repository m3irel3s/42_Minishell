/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/25 16:57:47 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_handle_syntax_error(void);
static t_status	ft_validate_pipe(t_token *current,
					t_token *prev);
static t_status	ft_validate_redirect(t_token *current);

/**
 * @brief Validates the syntax of all tokens in the shell structure.
 *
 * This function iterates through all tokens in the shell structure and
 * validates their syntax by calling the appropriate validation function.
 * If a syntax error is detected, an error message is printed and the
 * function returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the tokens.
 * @param tokens A pointer to the first token in the list.
 *
 * @return Returns SUCCESS if all tokens have valid syntax; otherwise,
 * returns ERROR.
 */
t_status	ft_validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens)
		return (ft_handle_syntax_error());
	current = tokens;
	prev = tokens->prev;
	if (current->type == PIPE)
	{
		if (ft_validate_pipe(current, prev) != SUCCESS)
			return (ERROR);
	}
	else if (current->type >= REDIRECT_IN && current->type <= HEREDOC)
	{
		if (ft_validate_redirect(current) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Prints a syntax error message and sets the shell's exit status to
 *        EXIT_FAILURE.
 *
 * This function is used to handle syntax errors detected during the
 * validation of tokens in the shell structure.
 *
 * @param shell A pointer to the shell structure containing the tokens.
 *
 * @return Returns ERROR.
 */
static t_status	ft_handle_syntax_error(void)
{
	return (ft_print_error(ERR_SYNTAX_VALIDATION_FAIL));
}

/**
 * @brief Validates the syntax of a pipe token.
 *
 * This function checks the validity of a pipe token by ensuring it is not
 * at the beginning of the input, not preceded by another pipe, and followed
 * by a token. If any of these conditions are not met, it prints a syntax
 * error message.
 *
 * @param shell A pointer to the shell structure for error handling.
 * @param current A pointer to the current pipe token being validated.
 * @param prev A pointer to the previous token in the list.
 *
 * @return Returns ERROR if the pipe syntax is invalid, otherwise SUCCESS.
 */

static t_status	ft_validate_pipe(t_token *current,
		t_token *prev)
{
	if (!prev || prev->type == PIPE || !current->next)
		return (ft_print_syntax_error("|"));
	return (SUCCESS);
}

/**
 * @brief Validates a redirection token.
 *
 * This function checks if a redirection token is followed by a valid
 * filename token. If the redirection token is not followed by a filename
 * token, it prints an error message and returns ERROR. If the filename
 * token is empty and the redirection type is HEREDOC, it prints an error
 * message and returns ERROR. Otherwise, it returns SUCCESS.
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @param current A pointer to the redirection token to be validated.
 *
 * @return Returns ERROR if the redirection token is not followed by a valid
 * filename token, otherwise returns SUCCESS.
 */
static t_status	ft_validate_redirect(t_token *current)
{
	if (!current->next)
		return (ft_print_redirect_no_file_error());
	if (current->next->type != WORD)
		return (ft_print_syntax_error(current->next->val.value));
	if (current->type == HEREDOC && ft_strlen(current->next->val.value) == 0)
		return (ft_print_heredoc_delim_error());
	return (SUCCESS);
}
