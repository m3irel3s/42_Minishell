/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 15:50:58 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_join_and_free(char *expanded_value, char *temp);
static void	ft_handle_quotes(char *input, size_t *i, int *quote_state);


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

/**
 * @brief Expands a token by processing special characters and variables.
 *
 * This function iterates through the given token, handling quotes and
 * expanding variables prefixed by the '$' character. It maintains the
 * current quote state to correctly handle quoted sections. The expanded
 * token is constructed by appending characters or expanded variables to
 * the resulting string, which is returned upon completion.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param token The token string to be expanded.
 * @return The expanded token as a string, or NULL if memory allocation fails.
 */

char	*ft_expand(t_shell *shell, char *token)
{
	char	*expanded_value;
	char	*temp;
	size_t	i;
	int		quote_state;

	quote_state = 0;
	i = 0;
	expanded_value = ft_safe_strdup("");
	if (!expanded_value)
		return (NULL);
	while (token[i])
	{
		ft_handle_quotes(token, &i, &quote_state);
		if (token[i] == '$' && quote_state != 1 && token[i + 1])
		{
			temp = ft_handle_dollar(shell, token, &i);
			expanded_value = ft_join_and_free(expanded_value, temp);
			continue ;
		}
		else
			expanded_value = ft_process_char(expanded_value, token[i]);
		i++;
		if (!expanded_value)
			return (NULL);
	}
	return (ft_free(token), expanded_value);
}
