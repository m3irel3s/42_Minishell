/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:11:23 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/11 16:22:44 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*ft_get_after_next(t_token *next_token);
static int		ft_is_redirect_token(int type);
static t_token	*ft_update_tokens(t_shell *shell, t_token *token,
					t_token *next_token, t_token *after_next);
static void		ft_create_and_add_redirect(t_token *token, t_shell *shell,
					t_redirect **last_redirect);

/**
 * @brief Creates a list of redirections from the shell's token list.
 *
 * This function iterates through the shell's token list, identifies
 * redirection tokens, and creates a linked list of redirection structures
 * based on these tokens. For each identified redirection token, it checks
 * if there is a following token representing the filename and creates a
 * redirection structure using `ft_create_and_add_redirect`. It updates the
 * token list to remove the redirection-related tokens using
 * `ft_update_tokens`. If a redirection token is found without a following
 * filename token, an error is printed and the function exits early.
 *
 * @param shell A pointer to the shell structure containing the token list.
 */
void	ft_create_redirection_list(t_shell *shell)
{
	t_token		*token;
	t_token		*next_token;
	t_token		*after_next;
	t_redirect	*last_redirect;

	token = shell->tokens;
	last_redirect = NULL;
	while (token)
	{
		next_token = token->next;
		after_next = ft_get_after_next(next_token);
		if (ft_is_redirect_token(token->type))
		{
			if (!next_token)
			{
				ft_print_redirect_no_file_error();
				return ;
			}
			ft_create_and_add_redirect(token, shell, &last_redirect);
			token = ft_update_tokens(shell, token, next_token, after_next);
		}
		else
			token = next_token;
	}
}

/**
 * @brief Gets the token after the next token in the token list.
 *
 * @param next_token A pointer to the next token in the token list.
 * @return Returns a pointer to the token after the next token, or NULL if
 * the next token is NULL (i.e., the end of the list has been reached).
 */
static t_token	*ft_get_after_next(t_token *next_token)
{
	if (!next_token)
		return (NULL);
	return (next_token->next);
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
 * @brief Updates the token list and frees the given token and next token.
 *
 * This function updates the token list by removing the given token and its
 * next token, and links the previous token to the token after the next token
 * (or sets the shell's tokens to NULL if the token is the first token in the
 * list). It also frees the given token and its next token.
 *

 * @param shell A pointer to the shell structure.
 * @param token The token to be removed.
 * @param next_token The token after the given token.
 * @param after_next The token after the next token.
 * @return The updated token list.
 */
static t_token	*ft_update_tokens(t_shell *shell, t_token *token,
	t_token *next_token, t_token *after_next)
{
	if (token->prev)
		token->prev->next = after_next;
	else
		shell->tokens = after_next;
	if (after_next)
		after_next->prev = token->prev;
	ft_free_token(token);
	ft_free_token(next_token);
	return (after_next);
}

/**
 * @brief Creates a new redirection from a token and adds it to the shell's
 *        redirection list.
 *
 * This function allocates a new redirection structure, initializes it based on
 * the provided token's type and its subsequent token's value and quoted status.
 * It then appends this redirection to the shell's list of redirections. If the
 * allocation of the redirection or its filename fails, the function frees any
 * allocated resources and returns without adding the redirection.
 *
 * @param token A pointer to the token representing the redirection operator.
 * @param shell A pointer to the shell structure where the redirection list is
 *              maintained.
 * @param last_redirect A double pointer to the last redirection in the list,
 *                      used to append the newly created redirection.
 */
static void	ft_create_and_add_redirect(t_token *token, t_shell *shell,
										t_redirect **last_redirect)
{
	t_redirect	*redirect;
	char		*del;

	redirect = ft_safe_calloc(sizeof(t_redirect));
	if (!redirect)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		return ;
	}
	redirect->type = token->type;
	del = ft_safe_strdup(token->next->val.value);
	if (!del)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		ft_free(redirect);
		return ;
	}
	redirect->filename = del;
	redirect->quoted = token->next->quoted;
	redirect->next = NULL;
	if (!(*last_redirect))
		shell->redirects = redirect;
	else
		(*last_redirect)->next = redirect;
	(*last_redirect) = redirect;
}
