/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 08:23:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_validate_pipe(t_shell *shell, t_token *current,
	t_token *prev);
static t_status	ft_validate_redirect(t_shell *shell, t_token *current);

/**
 * @brief Validates the syntax of a linked list of tokens.
 *
 * Checks that the linked list of tokens is syntactically valid. If the list
 * is invalid, prints an error message and updates the shell's exit status.
 * If valid, returns SUCCESS.
 *
 * @param shell The shell structure containing the linked list of tokens to
 * validate.
 * @param tokens The linked list of tokens to validate.
 * @return Returns SUCCESS if the linked list of tokens is syntactically valid;
 * otherwise, returns ERROR.
 */

t_status	ft_validate_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!shell || !tokens)
	{
		ft_putstr_fd(ERR_INVALID_PARAMS, STDERR_FILENO);
		if (shell)
			shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	current = tokens;
	prev = tokens->prev;
	while (current)
	{
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
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

/**
 * @brief Validates the syntax of a pipe token.
 *
 * Checks if the previous token is not a pipe and if there is a next token.
 * If not, prints an error message and sets the shell's exit status to
 * EXIT_FAILURE. Otherwise, returns SUCCESS.
 *
 * @param shell The shell structure containing the tokens to validate.
 * @param current The pipe token to validate.
 * @param prev The previous token of the pipe token.
 *
 * @return Returns SUCCESS if the pipe token is valid; otherwise, returns ERROR.
 */
static t_status	ft_validate_pipe(t_shell *shell, t_token *current,
		t_token *prev)
{
	if (!prev || prev->type == PIPE || !current->next)
		return (ft_print_syntax_error(shell, "|"));
	return (SUCCESS);
}

/**
 * @brief Validates the syntax of a redirection token.
 *
 * This function checks if the redirection token is followed by a valid
 * token. It ensures that a filename follows redirection tokens, and
 * that a valid delimiter follows heredoc tokens. If these conditions
 * are not met, the appropriate error message is printed.
 *
 * @param shell A pointer to the shell structure used for error reporting.
 * @param current A pointer to the current token being validated.
 *
 * @return Returns SUCCESS if the redirection token is valid; otherwise,
 * returns ERROR if there's no following valid token or if there is a
 * heredoc token with an empty delimiter.
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
