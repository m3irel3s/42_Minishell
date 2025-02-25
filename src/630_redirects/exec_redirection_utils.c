/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:11:23 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/25 10:05:08 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status		ft_extract_redirection_node(t_token *curr, t_shell *shell,
					t_redirect **last_redirect);
static t_token		*ft_remove_redirection_from_list(t_shell *shell,
					t_token *curr);
static int			ft_is_redirect_token(int type);
static t_status		ft_create_and_add_redirect(t_token *token, t_shell *shell,
					t_redirect **last_redirect);


/**
 * @brief Creates a list of redirections from the token list.
 *
 * This function iterates through the token list and for each redirection
 * operator token it extracts the redirection (using ft_extract_redirection_node)
 * and then removes the redirection tokens from the list (using
 * ft_remove_redirection_from_list).
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @return t_status SUCCESS if the list of redirections was successfully created,
 * ERROR otherwise.
 */
t_status	ft_create_redirection_list(t_shell *shell)
{
	t_token		*curr;
	t_redirect	*last_redirect;

	curr = shell->tokens;
	last_redirect = NULL;
	while (curr)
	{
		if (ft_is_redirect_token(curr->type))
		{
			if (ft_extract_redirection_node(curr, shell, &last_redirect) == ERROR)
				return (ERROR);
			curr = ft_remove_redirection_from_list(shell, curr);
		}
		else
			curr = curr->next;
	}
	return (SUCCESS);
}

/**
 * @brief Extracts a redirection from the token list and adds it to the list.
 *
 * Given a token (assumed to be a redirection operator) and its following token
 * (the filename/delimiter), this function creates a redirection structure and
 * appends it to the shell's redirection list.
 *
 * @param curr A pointer to the redirection operator token.
 * @param shell A pointer to the shell structure.
 * @param last_redirect A pointer to the pointer of the last redirection in the list.
 * @return t_status SUCCESS if the redirection node was created and added, ERROR otherwise.
 */
static t_status	ft_extract_redirection_node(t_token *curr, t_shell *shell,
	t_redirect **last_redirect)
{
	if (!curr->next)
		return (ft_print_error(ERR_SYNTAX_EOF_REDIR));
	if (!ft_create_and_add_redirect(curr, shell, last_redirect))
		return (ERROR);
	return (SUCCESS);
}


static t_token	*ft_remove_redirection_from_list(t_shell *shell, t_token *curr)
{
	t_token	*prev;
	t_token	*next_after_operand;

	if (!curr || !curr->next)
		return (NULL);
	prev = curr->prev;
	next_after_operand = curr->next->next;
	if (prev)
		prev->next = next_after_operand;
	else
		shell->tokens = next_after_operand;
	if (next_after_operand)
		next_after_operand->prev = prev;
	return (next_after_operand);
}

/**
 * @brief Determines if a token type corresponds to a redirection.
 *
 * This function checks if the provided token type is one of the redirection
 * types, such as REDIRECT_IN, REDIRECT_OUT, REDIRECT_APPEND, or HEREDOC.
 *
 * @param type The token type to be checked.
 * @return Returns 1 if the type is a redirection token, otherwise returns 0.
 */
static int	ft_is_redirect_token(int type)
{
	return (type == REDIRECT_IN
		|| type == REDIRECT_OUT
		|| type == HEREDOC
		|| type == REDIRECT_APPEND);
}

/**
 * @brief Creates a new redirection structure and adds it to the list.
 *
 * This function creates a new redirection structure using the current token
 * (the redirection operator) and its next token (the filename or delimiter). It
 * then appends this new node to the redirections list in the shell structure.
 *
 * @param token The redirection operator token.
 * @param shell A pointer to the shell structure.
 * @param last_redirect A pointer to the last redirection node in the list.
 * @return t_status SUCCESS if added successfully, ERROR otherwise.
 */
t_status	ft_create_and_add_redirect(t_token *token, t_shell *shell,
	t_redirect **last_redirect)
{
	t_redirect	*redirect;

	redirect = ft_safe_malloc(sizeof(t_redirect));
	if (!redirect)
		return (ft_print_error(ERR_MALLOC_FAIL));
	redirect->type = token->type;
	redirect->filename = ft_safe_strdup(token->next->value);
	if (!redirect->filename)
	{
		ft_free(redirect);
		return (ft_print_error(ERR_STRDUP_FAIL));
	}
	redirect->quoted = token->next->quoted;
	redirect->next = NULL;
	if (!(*last_redirect))
		shell->redirects = redirect;
	else
		(*last_redirect)->next = redirect;
	(*last_redirect) = redirect;
	return (SUCCESS);
}
