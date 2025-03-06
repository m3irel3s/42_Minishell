/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:15:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 16:22:12 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Processes a delimiter token and updates the token list with a new
 * filename token pointing to a temporary file.
 *
 * This function is responsible for updating the current token to represent a
 * redirection input, freeing its existing values, and setting its value to an
 * empty string. It creates a new token for the temporary file and inserts it
 * into the token list, updating the pointers accordingly. The delimiter token
 * is freed after its pointers are adjusted.
 *
 * @param current The current token to be updated.
 * @param delim The delimiter token to be processed and removed.
 * @param tempfile The name of the temporary file to be used in the new token.
 */

static void	ft_process_delimiter(t_token *current, t_token *delim, char *tempfile)
{
	t_token	*filename_token;

	current->type = REDIRECT_IN;
	ft_free(current->val.value);
	current->val.value = ft_safe_strdup("");
	ft_free(current->val.og_value);
	current->val.og_value = ft_safe_strdup("");
	filename_token = ft_safe_calloc(sizeof(t_token));
	if (!filename_token)
		return ;
	filename_token->type = WORD;
	filename_token->val.value = ft_safe_strdup(tempfile);
	filename_token->val.og_value = ft_safe_strdup(tempfile);
	filename_token->quoted = 0;
	filename_token->prev = current;
	filename_token->next = delim->next;
	current->next = filename_token;
	if (delim->next)
		delim->next->prev = filename_token;
	ft_free_token(delim);
}
