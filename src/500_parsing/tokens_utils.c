/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/03 15:31:05 by meferraz         ###   ########.fr       */
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

t_token	*ft_create_token(char *value, t_token_type type)
{
	t_token *new_token;

	new_token = ft_safe_malloc(sizeof(t_token));
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}
