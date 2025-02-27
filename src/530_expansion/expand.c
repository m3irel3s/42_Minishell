/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 09:56:50 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//static char	*ft_handle_expansion_error(void);
static char	*ft_join_and_free(char *expanded_value, char *temp);
//static char	*ft_handle_null_expansion(char *expanded_value);


/**
 * @brief Handles an expansion error, setting the shell's exit status to failure.
 *
 * This function is used when an error occurs during token expansion. It sets the
 * shell's exit status to failure and returns NULL.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @return NULL to indicate that an error occurred.
 */
// static char	*ft_handle_expansion_error(void)
// {
// 	g_exit_status = EXIT_FAILURE;
// 	return (NULL);
// }

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
 * @brief Handles quotes in the input string.
 *
 * This function updates the quote state based on the current character
 * in the input string.
 *
 * @param input The input string.
 * @param i A pointer to the current index in the input string.
 * @param quote_state A pointer to the current quote state.
 */
static void ft_handle_quotes(char *input, size_t *i, int *quote_state)
{
	if (input[*i] == '\'' && *quote_state != 2)
	{
		if (*quote_state == 1)
			*quote_state = 0;
		else
			*quote_state = 1;
	}
	else if (input[*i] == '\"' && *quote_state != 1)
	{
		if (*quote_state == 2)
			*quote_state = 0;
		else
			*quote_state = 2;
	}
}

/**
 * @brief Expands a token in the input string.
 *
 * This function handles the expansion of a token in the input string,
 * including handling quotes and dollar signs.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param input The input string to be expanded.
 * @param i A pointer to the current index in the input string.
 * @param quote_state A pointer to the current quote state.
 * @return The expanded token string.
 */
static char *ft_expand_token(t_shell *shell, char *input, size_t *i, int *quote_state)
{
	char *expanded_value;
	char *temp;

	expanded_value = ft_safe_strdup("");
	if (!expanded_value)
		return (NULL);

	while (input[*i])
	{
		ft_handle_quotes(input, i, quote_state);
		if (input[*i] == '$' && *quote_state != 1)
		{
			temp = ft_handle_dollar(shell, input, i);
			expanded_value = ft_join_and_free(expanded_value, temp);
			continue ;
		}
		else
			expanded_value = ft_process_char(expanded_value, input[*i]);
		(*i)++;
		if (!expanded_value)
			return (NULL);
	}
	return (expanded_value);
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
// static char	*ft_handle_null_expansion(char *expanded_value)
// {
// 	char	*result;

// 	result = ft_safe_strjoin(expanded_value, "", 1);
// 	if (!result)
// 		return (ft_handle_expansion_error());
// 	return (result);
// }

/**
 * @brief Expands the input string in the shell structure.
 *
 * This function expands the input string by replacing any '$' characters with
 * their expanded values. It also handles quoted strings and ensures that quotes
 * are properly matched.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @return SUCCESS if the input is expanded successfully, or an error status if
 * there is a memory allocation failure or unmatched quotes.
 */
t_status ft_expand(t_shell *shell)
{
	char *expanded_value;
	char *new_expanded_value;
	size_t i;
	int quote_state;

	quote_state = 0;
	i = 0;
	expanded_value = NULL;
	new_expanded_value = NULL;
	if (!shell || !shell->input)
		return (ft_print_error(ERR_INVALID_SHELL_OR_INPUT));
	while (shell->input[i])
	{
		new_expanded_value = ft_expand_token(shell, shell->input, &i, &quote_state);
		if (!new_expanded_value)
			return (ft_free(expanded_value), ft_print_error(ERR_EXPANSION_FAIL));
		ft_free(expanded_value);
		expanded_value = new_expanded_value;
	}
	ft_free(shell->input);
	shell->input = expanded_value;
	return (SUCCESS);
}
