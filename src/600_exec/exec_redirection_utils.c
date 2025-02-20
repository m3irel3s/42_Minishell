/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:11:23 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 10:30:54 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_create_and_add_redirect(t_token *token, t_shell *shell,
				t_redirect **last_redirect);

/**
 * @brief Creates a linked list of redirection tokens from the shell's tokens.
 *
 * This function iterates through the shell's list of tokens and identifies
 * tokens that represent redirection operators (e.g., REDIRECT_IN, REDIRECT_OUT,
 * HEREDOC, REDIRECT_APPEND). For each redirection token found, it calls
 * ft_create_and_add_redirect to add the redirection to the shell's redirection
 * list.
 *
 * @param shell A pointer to the shell structure containing the token list from
 *              which redirection tokens are to be extracted and added to the
 *              redirection list.
 */
void ft_create_redirection_list(t_shell *shell)
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
		if (!next_token)
			after_next = NULL;
		else
			after_next = next_token->next;
		if (token->type == REDIRECT_IN
			|| token->type == REDIRECT_OUT
			|| token->type == HEREDOC
			|| token->type == REDIRECT_APPEND)
		{
			if (!next_token)
			{
				ft_print_redirect_no_file_error();
				return ;
			}
			ft_create_and_add_redirect(token, shell, &last_redirect);
			if (token->prev)
				token->prev->next = after_next;
			else
				shell->tokens = after_next;
			if (after_next)
				after_next->prev = token->prev;
			free(token->value);
			free(token);
			free(next_token->value);
			free(next_token);
			token = after_next;
		}
		else
			token = next_token;
	}
}

/**
 * @brief Creates a new redirection token from a token and adds it to the
 *        shell's redirection list.
 *
 * This function allocates memory for a new redirection token and copies the
 * value of the given token into the new redirection token. It then finds the
 * last redirection token in the shell's redirection list and appends the new
 * redirection token to the list. If the shell's redirection list is initially
 * empty, the new redirection token becomes the first token in the list.
 *
 * @param token A pointer to the token whose value is to be copied into the
 *              new redirection token.
 * @param shell A pointer to the shell structure containing the redirection
 *              list to which the new redirection token is to be added.
 */
static void	ft_create_and_add_redirect(t_token *token, t_shell *shell,
										t_redirect **last_redirect)
{
	t_redirect	*redirect;

	redirect = ft_safe_malloc(sizeof(t_redirect));
	if (!redirect)
		return ;
	redirect->type = token->type;
	redirect->filename = ft_strdup_safe(token->next->value);
	redirect->quoted = token->next->quoted;
	if (!redirect->filename)
		return (ft_free(redirect));
	redirect->next = NULL;
	if (!(*last_redirect))
		shell->redirects = redirect;
	else
		(*last_redirect)->next = redirect;
	(*last_redirect) = redirect;
}
