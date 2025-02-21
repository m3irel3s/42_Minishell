/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 17:22:39 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_token(t_shell *shell, char *token, int quoted);
static char	*ft_handle_expansion_error(void);
static char	*ft_join_and_free(char *expanded_value, char *temp);
static char	*ft_handle_null_expansion(char *expanded_value);

/**
 * @brief Expands all tokens in the shell's linked list.
 *
 * Iterates through the shell's linked list of tokens and expands each token by
 * calling ft_expand_token. The expanded token value is then stored in the
 * token's value field, and the original token value is freed. If memory
 * allocation fails during expansion, the function sets the shell's exit status
 * to failure and returns an error status.
 *
 * @param shell A pointer to the shell structure containing the linked list of
 * tokens to be expanded.
 * @return SUCCESS if all tokens are expanded successfully, or ERROR if there
 * is a memory allocation failure.
 */
t_status	ft_expand(t_shell *shell)
{
	t_token	*current;
	char	*expanded_value;

	if (!shell)
		return (ft_print_error(ERR_INVALID_SHELL));
	if (!shell->tokens)
		return (SUCCESS);
	current = shell->tokens;
	while (current)
	{
		expanded_value = ft_expand_token(shell, current->value,
				current->quoted);
		if (!expanded_value)
		{
			g_exit_status = EXIT_FAILURE;
			return (ERROR);
		}
		ft_free(current->value);
		current->value = expanded_value;
		current = current->next;
	}
	return (SUCCESS);
}

/**
 * @brief Expands a single token, replacing any '$' characters with their values.
 *
 * This function iterates through the token, replacing any '$' characters with
 * their expanded values using ft_handle_dollar. The expanded value is then
 * returned.
 * If memory allocation fails, the function sets the shell's exit status to
 * failure and returns NULL.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param token The token to be expanded.
 * @param quoted A boolean indicating if the token is quoted.
 * @return The expanded token value as a string, or NULL on failure.
 */
static char	*ft_expand_token(t_shell *shell, char *token, int quoted)
{
	char	*expanded_value;
	char	*temp;
	size_t	i;

	if (!token)
		return (ft_safe_strdup(""));
	expanded_value = ft_safe_strdup("");
	if (!expanded_value)
		return (ft_handle_expansion_error());
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !quoted)
		{
			temp = ft_handle_dollar(shell, token, &i);
			if (temp)
				expanded_value = ft_join_and_free(expanded_value, temp);
			else
				expanded_value = ft_handle_null_expansion(expanded_value);
		}
		else
			expanded_value = ft_process_char(expanded_value, token[i++]);
		if (!expanded_value)
			return (ft_handle_expansion_error());
	}
	return (expanded_value);
}

/**
 * @brief Joins two strings, freeing the second string after the join.
 *
 * This function is used to join a temporary string to the expanded value of a
 * token, freeing the temporary string after the join.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param expanded_value The current expanded value of a token.
 * @param temp The temporary string to be joined.
 * @return The joined string.
 */
static char	*ft_join_and_free(char *expanded_value, char *temp)
{
	char	*result;

	result = ft_safe_strjoin(expanded_value, temp, 1);
	ft_free(temp);
	return (result);
}

/**
 * @brief Handles an expansion error, setting the shell's exit status to failure.
 *
 * This function is used when an error occurs during token expansion. It sets the
 * shell's exit status to failure and returns NULL.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @return NULL to indicate that an error occurred.
 */
static char	*ft_handle_expansion_error(void)
{
	g_exit_status = EXIT_FAILURE;
	return (NULL);
}

/**
 * @brief Processes a single character in a token during expansion.
 *
 * This function takes a character and appends it to the current expanded value.
 * If the expanded value is NULL, it is set to a string containing only the
 * character.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param expanded_value The current expanded value to which the character will
 * be appended.
 * @param c The character to be processed.
 * @return The updated expanded value with the character appended, or a new
 * string containing only the character if the expanded value was NULL.
 */
char	*ft_process_char(char *expanded_value, char c)
{
	char	c_str[2];
	char	*new_expanded;

	c_str[0] = c;
	c_str[1] = '\0';
	new_expanded = ft_safe_strjoin(expanded_value, c_str, 1);
	return (new_expanded);
}

/**
 * @brief Handles the scenario where a variable expansion results in NULL.
 *
 * This function safely joins the current expanded value with an empty string,
 * ensuring that the expansion process can continue without issues. If memory
 * allocation fails during the operation, it calls the error handling function
 * and returns NULL.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param expanded_value The current expanded value to which the empty string
 * will be appended.
 * @return The updated expanded value with an empty string appended, or NULL
 * if a memory allocation error occurs.
 */
static char	*ft_handle_null_expansion(char *expanded_value)
{
	char	*result;

	result = ft_safe_strjoin(expanded_value, "", 1);
	if (!result)
		return (ft_handle_expansion_error());
	return (result);
}
