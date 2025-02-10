/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:03:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 10:43:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Determines the type of token based on its value.
 *
 * This function takes a pointer to a string and its length as input and
 * returns the type of token that the string represents. It checks for
 * single character operators and multiple character operators, and
 * returns the appropriate type. If the string does not match any of
 * the known operators, it returns WORD.
 *
 * @param value A pointer to the string to be checked.
 * @param len The length of the string.
 * @return The type of token represented by the string.
 */
t_token_type	ft_determine_token_type(char *value, size_t len)
{
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
 * @brief Calculates the length of the given operator.
 *
 * This function takes a string starting with an operator (either '<', '>', or
 * '>>') and returns the length of the operator. If the operator is '>>' or '<<',
 * the length is 2; otherwise, the length is 1.
 *
 * @param input The string starting with an operator.
 *
 * @return The length of the operator.
 */
size_t	ft_get_operator_length(const char *input)
{
	if (input[0] == '>' && input[1] == '>')
		return (2);
	if (input[0] == '<' && input[1] == '<')
		return (2);
	return (1);
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
 * @brief Creates a new token with the given value and type and adds it to the
 *        end of the token linked list.
 *
 * This function allocates memory for a new token and populates it with the
 * given value and type. It then adds the new token to the end of the token
 * linked list in the shell structure.
 *
 * @param shell A pointer to the shell structure containing the token linked
 *              list.
 * @param start The start index of the value in the shell's input string.
 * @param end The end index of the value in the shell's input string.
 * @param type The type of the token, which is one of PIPE, REDIRECT_IN,
 *              REDIRECT_OUT, REDIRECT_APPEND, HEREDOC, or WORD.
 * @return Returns SUCCESS if the token is successfully created and added to
 *         the list; otherwise, returns ERROR.
 */
int	ft_create_and_add_token(t_shell *shell, size_t start, size_t end, t_token_type type)
{
	t_token *new_token;
	t_token *last_token;

	if (!shell || !shell->input)
		return (ERROR);
	new_token = ft_safe_malloc(sizeof(t_token));
	if (!new_token)
		return (ERROR);
	new_token->value = ft_substr(shell->input, start, end - start);
	if (!new_token->value)
	{
		free(new_token);
		return (ERROR);
	}
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!shell->tokens)
		shell->tokens = new_token;
	else
	{
		last_token = shell->tokens;
		while (last_token->next)
			last_token = last_token->next;
		last_token->next = new_token;
		new_token->prev = last_token;
	}
	return (SUCCESS);
}
