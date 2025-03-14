/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/14 17:43:20 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_join_and_free(char *expanded_value, char *temp);
static void	ft_handle_quotes(char *input, size_t *i, int *quote_state);
static char	*ft_expand_loop(t_shell *shell, char *token, char *expanded_value);

/**
 * @brief Expands any variables in a token.
 *
 * This function takes a shell structure and a token string, and expands any
 * variables found in the token string. It returns a new string with the
 * variables expanded. If memory allocation fails, the function sets the
 * shell's exit status to failure and returns NULL.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param token The token string containing the variables to be expanded.
 * @return The expanded value of the variables as a string, or NULL if memory
 * allocation fails.
 */
char	*ft_expand(t_shell *shell, char *token)
{
	char	*expanded_value;

	expanded_value = ft_safe_strdup("");
	if (!expanded_value)
		return (NULL);
	expanded_value = ft_expand_loop(shell, token, expanded_value);
	if (!expanded_value)
		return (NULL);
	ft_free(token);
	return (expanded_value);
}

/**
 * @brief Loop through a token and expand any found variables.
 *
 * This function iterates over a token string, checking for quotes and
 * variable expansion. If a variable is found, it calls ft_handle_dollar
 * to expand the variable. If a quote is found, it calls ft_handle_quotes
 * to handle the quote state. It also appends non-variable characters to
 * the expanded value string. If memory allocation fails, the function
 * returns NULL.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param token The token string to be looped through.
 * @param expanded_value The current expanded value of a token.
 * @return The final expanded value of a token, or NULL if memory allocation
 * fails.
 */
static char	*ft_expand_loop(t_shell *shell, char *token, char *expanded_value)
{
	char	*temp;
	size_t	i;
	int		quote_state;

	i = 0;
	quote_state = 0;
	while (token[i])
	{
		ft_handle_quotes(token, &i, &quote_state);
		if (token[i] == '$' && quote_state != 1 && token[i + 1])
		{
			temp = ft_handle_dollar(shell, token, &i);
			expanded_value = ft_join_and_free(expanded_value, temp);
			continue ;
		}
		expanded_value = ft_process_char(expanded_value, token[i]);
		i++;
		if (!expanded_value)
			return (NULL);
	}
	return (expanded_value);
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
static void	ft_handle_quotes(char *input, size_t *i, int *quote_state)
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
