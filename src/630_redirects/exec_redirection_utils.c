/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:11:23 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 15:58:08 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_get_after_next(t_token *next_token);
static int		ft_is_redirect_token(int type);
static t_token	*ft_update_tokens(t_shell *shell, t_token *token,
					t_token *next_token, t_token *after_next);
static t_status		ft_create_and_add_redirect(t_token *token, t_shell *shell,
					t_redirect **last_redirect);


/**
 * @brief Creates a list of redirections from the token list.
 *
 * This function iterates through the token list and creates a new redirection
 * structure for each token that is a redirection operator. It checks if the
 * redirection operator is followed by a filename token, and if not, prints an
 * error message and returns ERROR. If the redirection operator is followed by a
 * filename token, it creates a new redirection structure and adds it to the
 * list of redirections. It then updates the token list by removing the
 * redirection operator token and its next token (the filename token).
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @return t_status SUCCESS if the list of redirections was successfully created,
 * ERROR otherwise.
 */
t_status	ft_create_redirection_list(t_shell *shell)
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
				return (ft_print_error(shell, ERR_SYNTAX_EOF_REDIR));
			if (!ft_create_and_add_redirect(token, shell, &last_redirect))
				return (ERROR);
			token = ft_update_tokens(shell, token, next_token, after_next);
		}
		else
			token = next_token;
	}
	return (SUCCESS);
}

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

/*************  ✨ Codeium Command ⭐  *************/
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
 * @brief Creates a new redirection structure and adds it to the list of redirections.
 *
 * This function creates a new redirection structure from the given token and adds
 * it to the list of redirections in the shell structure. If the list of redirections
 * is empty, it sets the shell's redirects field to the new redirection structure.
 * Otherwise, it links the new redirection structure to the last redirection structure
 * in the list. It also sets the quoted field of the new redirection structure to the
 * quoted field of the given token's next token (the filename token).
 *
 * @param token The token to be used to create the new redirection structure.
 * @param shell A pointer to the shell structure containing the list of redirections.
 * @param last_redirect A pointer to the last redirection structure in the list of
 * redirections.
 * @return t_status SUCCESS if the new redirection structure was successfully added
 * to the list of redirections, ERROR otherwise.
 */
static t_status	ft_create_and_add_redirect(t_token *token, t_shell *shell,
	t_redirect **last_redirect)
{
	t_redirect	*redirect;

	redirect = ft_safe_malloc(sizeof(t_redirect));
	if (!redirect)
		return (ft_print_error(shell, ERR_MALLOC_FAIL));
	redirect->type = token->type;
	redirect->filename = ft_safe_strdup(token->next->value);
	if (!redirect->filename)
	{
		free(redirect);
		return (ft_print_error(shell, ERR_STRDUP_FAIL));
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

