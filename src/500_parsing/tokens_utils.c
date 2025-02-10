/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 10:00:58 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/**
 * @brief Determines the token type based on the given string value.
 *
 * This function analyzes the input string and returns the corresponding
 * token type. It checks for operators like pipe '|', input redirection '<',
 * output redirection '>', heredoc '<<', and append redirection '>>'. If the
 * input string does not match any predefined operators, it defaults to
 * returning WORD as the token type.
 *
 * @param value The string value to be analyzed for its token type.
 *
 * @return The token type corresponding to the input string, which can be
 *         PIPE, REDIRECT_IN, REDIRECT_OUT, HEREDOC, REDIRECT_APPEND, or WORD.
 */

t_token_type	ft_determine_token_type(char *value)
{
	size_t	len;

	len = ft_strlen(value);
	if (len == 1)
	{
		if (*value == '|')
			return (PIPE);
		else if (*value == '<')
			return (REDIRECT_IN);
		else if (*value == '>')
			return (REDIRECT_OUT);
	}
	else if (len == 2)
	{
		if (ft_strncmp(value, "<<", 2) == 0)
			return (HEREDOC);
		if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	}
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
/**
 * @brief Creates a token from the current input segment and adds it to the shell's token list.
 *
 * @param shell A pointer to the shell structure.
 * @param start The starting index of the token in the input string.
 * @param end The ending index of the token in the input string.
 * @return Returns SUCCESS if the token creation succeeds, ERROR otherwise.
 */
t_status ft_create_and_add_token(t_shell *shell, size_t start, size_t end)
{
	char *temp = ft_substr(shell->input, start, end - start);
	if (!temp)
		return (ERROR);
	t_token *token = ft_create_token(temp, ft_determine_token_type(temp));
	free(temp);
	if (!token)
		return (ERROR);
	ft_add_token_to_list(shell, token);
	return (SUCCESS);
}
