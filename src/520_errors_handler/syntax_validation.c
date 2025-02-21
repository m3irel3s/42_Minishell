/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 13:54:51 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_handle_syntax_error(t_shell *shell);
static t_status	ft_validate_pipe(t_shell *shell, t_token *current,
					t_token *prev);
static t_status	ft_validate_redirect(t_shell *shell, t_token *current);

/**
 * @brief Validates the syntax of all tokens in the shell structure.
 *
 * Checks if a pipe token is at the start of the list, or if it is preceded
 * by another pipe token, or if it is the last token in the list. Also checks
 * if a redirection token is at the start of the list, or if it is followed
 * by a non-redirect token, or if it is the last token in the list. If any of
 * these conditions are true, prints an error message and sets the shell's
 * exit status to EXIT_FAILURE.
 *
 * @param shell A pointer to the shell structure containing the tokens.
 * @param tokens The first token in the list of tokens to be validated.
 *
 * @return Returns SUCCESS if all tokens have valid syntax; otherwise,
 * returns ERROR.
 */
t_status	ft_validate_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens || !shell)
		return (ft_handle_syntax_error(shell));
	current = tokens;
	prev = tokens->prev;
	if (current->type == PIPE)
	{
		if (ft_validate_pipe(shell, current, prev) != SUCCESS)
			return (ERROR);
	}
	else if (current->type >= REDIRECT_IN && current->type <= HEREDOC)
	{
		if (ft_validate_redirect(shell, current) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Handles a syntax error by printing an error message and setting the
 *        shell's exit status to EXIT_FAILURE.
 *
 * @param shell The shell struct to update the exit status.
 *
 * @return Returns ERROR, indicating that an error was found.
 */
static t_status	ft_handle_syntax_error(t_shell *shell)
{
	ft_putstr_fd(ERR_SYNTAX_VALIDATION_FAIL, STDERR_FILENO);
	if (shell)
		shell->exit_status = EXIT_FAILURE;
	return (ERROR);
}

/**
 * @brief Validates a pipe token.
 *
 * Checks if the pipe token is at the start of the list, or if it is preceded
 * by another pipe token, or if it is the last token in the list. If any of
 * these conditions are true, prints an error message and returns ERROR.
 *
 * @param shell The shell struct containing the exit status.
 * @param current The current token being validated.
 * @param prev The previous token in the list.
 *
 * @return Returns SUCCESS if the pipe token is valid, otherwise returns ERROR.
 */
static t_status	ft_validate_pipe(t_shell *shell, t_token *current,
		t_token *prev)
{
	if (!prev || prev->type == PIPE || !current->next)
		return (ft_print_syntax_error(shell, "|"));
	return (SUCCESS);
}

/**
 * @brief Validates a redirection token.
 *
 * This function checks if the redirection token is valid:
 * - Checks if there is a following token (the filename).
 * - Checks if the following token is a WORD token.
 * - Checks if the redirection token is a HEREDOC and if its value is not empty.
 *
 * @param shell A pointer to the shell structure.
 * @param current The redirection token to be validated.
 *
 * @return Returns SUCCESS if the redirection token is valid; otherwise,
 * returns ERROR.
 */
static t_status	ft_validate_redirect(t_shell *shell, t_token *current)
{
	if (!current->next)
		return (ft_print_redirect_no_file_error(shell));
	if (current->next->type != WORD)
		return (ft_print_syntax_error(shell, current->next->value));
	if (current->type == HEREDOC && ft_strlen(current->next->value) == 0)
		return (ft_print_heredoc_delim_error(shell));
	return (SUCCESS);
}
