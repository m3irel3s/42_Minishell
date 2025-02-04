/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 11:39:22 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Determines the token type based on the provided string.
 *
 * This function takes a string representing a token value and returns its
 * corresponding token type. The token types include PIPE, REDIRECT_IN,
 * REDIRECT_OUT, REDIRECT_APPEND, HEREDOC, and WORD. It uses string comparison
 * to match the input value to known shell operators and returns the appropriate
 * token type. If no specific type is matched, it defaults to WORD.
 *
 * @param value The string representing the token value.
 * @return The token type corresponding to the input string.
 */
t_token_type	ft_determine_token_type(char *value)
{
	size_t	value_len;

	value_len = ft_strlen(value);
	if (!ft_strncmp(value, "|", value_len))
		return (PIPE);
	if (!ft_strncmp(value, "<", value_len))
		return (REDIRECT_IN);
	if (!ft_strncmp(value, ">", value_len))
		return (REDIRECT_OUT);
	if (!ft_strncmp(value, ">>", value_len))
		return (REDIRECT_APPEND);
	if (!ft_strncmp(value, "<<", value_len))
		return (HEREDOC);
	return (WORD);
}

/**
 * @brief Creates a new token from a given value and type.
 *
 * This function allocates memory for a new token and populates it with the
 * provided value and type. It then returns the new token.
 *
 * @param value The string representing the token value.
 * @param type The type of the token, which is one of PIPE, REDIRECT_IN,
 *              REDIRECT_OUT, REDIRECT_APPEND, HEREDOC, or WORD.
 * @return The newly allocated token.
 */
t_token	*ft_create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = ft_safe_malloc(sizeof(t_token));
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/**
 * @brief Adds a new token to the end of the token linked list.
 *
 * This function traverses the linked list of tokens in the shell structure and
 * adds the newly created token to the end of the list. If the list is empty, it
 * sets the shell's tokens pointer to the new token.
 *
 * @param shell A pointer to the shell structure containing the token linked
 *              list.
 * @param new_token A pointer to the newly created token to be added to the
 *                  list.
 */
void	ft_add_token_to_list(t_shell *shell, t_token *new_token)
{
	t_token	*current;

	current = shell->tokens;
	if (!current)
	{
		shell->tokens = new_token;
		return ;
	}
	while (current->next)
		current = current->next;
	new_token->prev = current;
	current->next = new_token;
}
