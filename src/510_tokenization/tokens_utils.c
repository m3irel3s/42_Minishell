/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/13 16:12:00 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token_type	ft_check_single_char(char *value);
static t_token_type	ft_check_double_char(char *value);

/**
 * @brief Checks the given string and returns its corresponding token type.
 *
 * Checks the given string and returns its corresponding token type.
 * If the string is a single character, checks for single character tokens.
 * If the string is two characters long, checks for double character tokens.
 * If the string does not match any special tokens, returns WORD.
 *
 * @param value The string to be checked.
 * @param len The length of the string to be checked.
 *
 * @return Returns the corresponding token type.
 */
t_token_type	ft_determine_token_type(char *value, size_t len)
{
	if (len == 1)
		return (ft_check_single_char(value));
	if (len == 2)
		return (ft_check_double_char(value));
	return (WORD);
}

/**
 * @brief Checks a single character and returns its corresponding token type.
 *
 * Checks if the given string is a single character and if it is a special
 * character, returns its corresponding token type. If not, returns WORD.
 *
 * @param value String to be checked.
 *
 * @return Returns the corresponding token type.
 */
static t_token_type	ft_check_single_char(char *value)
{
	if (*value == '|')
		return (PIPE);
	else if (*value == '<')
		return (REDIRECT_IN);
	else if (*value == '>')
		return (REDIRECT_OUT);
	else if(*value == '=')
		return (EQUAL);
	return (WORD);
}

/**
 * @brief Checks the given string and returns its corresponding token type.
 *
 * Checks the given string and returns its corresponding token type.
 * If the string is two characters long, checks for double character tokens.
 * If the string does not match any special tokens, returns WORD.
 *
 * @param value The string to be checked.
 *
 * @return Returns the corresponding token type.
 */
static t_token_type	ft_check_double_char(char *value)
{
	if (ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	return (WORD);
}

/**
 * @brief Creates a new token with the given value and type.
 *
 * This function allocates memory for a new token, copies the given value
 * into the new token, and sets the new token's type and next/prev pointers.
 * If memory allocation fails, the function returns NULL.
 *
 * @param value The value of the token to be created.
 * @param type The type of the token to be created.
 *
 * @return Returns a pointer to the newly created token if successful;
 *         otherwise, returns NULL.
 */
t_token	*ft_create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = ft_safe_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup_safe(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/**
 * @brief Adds a new token to the end of the shell's token list.
 *
 * This function appends a new token to the end of the linked list of tokens
 * within the shell structure. If the token list is initially empty, the new
 * token becomes the first token in the list. The function ensures that the
 * previous pointer of the new token is correctly set to the last token in
 * the list before the new token is added.
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @param new_token A pointer to the new token to be added to the list.
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
