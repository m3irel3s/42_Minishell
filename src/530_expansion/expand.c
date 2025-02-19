/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/19 15:06:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_token(t_shell *shell, char *token, int quoted);
static char	*ft_process_char(char *expanded_value, char c);

/**
 * @brief Expand tokens in the token list, replacing '$' with their expanded
 *        values.
 *
 * This function iterates through the token list, expanding each token by calling
 * ft_expand_token. If any expansion fails (i.e. returns NULL), the function
 * immediately returns ERROR. Otherwise, it replaces the original token value
 * with the expanded value and moves on to the next token.
 *
 * @param shell The shell struct containing the token list and environment info.
 * @return SUCCESS if all tokens expanded successfully, ERROR otherwise.
 */
t_status	ft_expand(t_shell *shell)
{
	t_token	*current;
	char	*expanded_value;

	current = shell->tokens;
	while (current)
	{
		expanded_value = ft_expand_token(shell, current->value,
				current->quoted);
		if (!expanded_value)
			return (ERROR);
		ft_free(current->value);
		current->value = expanded_value;
		current = current->next;
	}
	return (SUCCESS);
}

/**
 * @brief Expands a single token, replacing '$' characters with their expanded
 *        values according to the shell's environment.
 *
 * This function iterates through the token string, replacing any '$' characters
 * with their expanded values using ft_handle_dollar. If the token is quoted,
 * '$' characters are treated as literal characters.
 *
 * @param shell The shell struct containing the environment info.
 * @param token The string token to be expanded.
 * @param quoted The quoted status of the token (1 if quoted, 0 otherwise).
 * @return The expanded token value as a string, or NULL if an error occurred.
 */
static char	*ft_expand_token(t_shell *shell, char *token, int quoted)
{
	char	*expanded_value;
	char	*temp;
	size_t	i;

	expanded_value = ft_strdup("");
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && quoted != 1)
		{
			temp = ft_handle_dollar(shell, token, &i);
			if (temp)
			{
				expanded_value = ft_strjoin_gnl(expanded_value, temp);
				ft_free(temp);
			}
		}
		else
		{
			expanded_value = ft_process_char(expanded_value, token[i]);
			i++;
		}
	}
	return (expanded_value);
}

/**
 * @brief Appends a character to the expanded value string.
 *
 * This function takes an expanded value string and a character, converts
 * the character to a string, appends it to the expanded value, and returns
 * the new expanded value. The original expanded value is freed.
 *
 * @param expanded_value The current expanded value string.
 * @param c The character to be appended to the expanded value.
 * @return The new expanded value string with the character appended.
 */

static char	*ft_process_char(char *expanded_value, char c)
{
	char	c_str[2];
	char	*new_expanded;

	c_str[0] = c;
	c_str[1] = '\0';
	new_expanded = ft_strjoin(expanded_value, c_str);
	ft_free(expanded_value);
	return (new_expanded);
}
