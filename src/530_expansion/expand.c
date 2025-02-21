/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 11:11:21 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_token(t_shell *shell, char *token, int quoted);
static char	*ft_handle_expansion_error(t_shell *shell);
static char	*ft_join_and_free(t_shell *shell, char *expanded_value, char *temp);

/**
 * @brief Expands all tokens in the shell by replacing any '$' characters with
 *        their environment values.
 *
 * This function iterates through all tokens in the shell and expands any tokens
 * that contain a '$' character. The expanded string is then placed in the
 * token's value field.
 *
 * @param shell The shell struct containing the tokens to be expanded.
 *
 * @return SUCCESS if all tokens are successfully expanded, otherwise ERROR.
 */
t_status	ft_expand(t_shell *shell)
{
	t_token	*current;
	char	*expanded_value;

	if (!shell || !shell->tokens)
	{
		ft_putstr_fd(ERR_INVALID_PARAMS, STDERR_FILENO);
		if (shell)
			shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	current = shell->tokens;
	while (current)
	{
		expanded_value = ft_expand_token(shell, current->value,
				current->quoted);
		if (!expanded_value)
		{
			shell->exit_status = EXIT_FAILURE;
			return (ERROR);
		}
		ft_free(current->value);
		current->value = expanded_value;
		current = current->next;
	}
	return (SUCCESS);
}

/**
 * @brief Expands a token string to replace any '$' characters with their
 *        environment values.
 *
 * This function iterates through the input token string, replacing any '$'
 * characters with their environment values using ft_handle_dollar. The
 * expanded string is then returned. If memory allocation fails, the function
 * returns NULL and the shell's exit status is set to EXIT_FAILURE.
 *
 * @param shell The shell structure containing environment and state info.
 * @param token The input token string to be expanded.
 * @param quoted Whether the token is quoted (1 if quoted, 0 otherwise).
 *
 * @return A string representing the expanded value, or NULL on failure.
 */
static char	*ft_expand_token(t_shell *shell, char *token, int quoted)
{
	char	*expanded_value;
	char	*temp;
	size_t	i;

	if (!token)
		return (NULL);
	expanded_value = ft_safe_strdup("");
	if (!expanded_value)
		return (ft_handle_expansion_error(shell));
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && quoted != 1)
		{
			temp = ft_handle_dollar(shell, token, &i);
			if (temp)
				expanded_value = ft_join_and_free(shell, expanded_value, temp);
		}
		else
			expanded_value = ft_process_char(shell, expanded_value, token[i++]);
		if (!expanded_value)
			return (ft_handle_expansion_error(shell));
	}
	return (expanded_value);
}

/**
 * @brief Concatenates two strings using ft_strjoin_gnl and frees them.
 *
 * This function is used to concatenate the expanded value with the temp string
 * and then free both the expanded value and temp strings.
 *
 * @param expanded_value Expanded value string.
 * @param temp Temporary string.
 * @return The concatenated string.
 */
static char	*ft_join_and_free(t_shell *shell, char *expanded_value, char *temp)
{
	char	*result;

	result = ft_safe_strjoin(shell, expanded_value, temp, 1);
	ft_free(temp);
	return (result);
}

/**
 * @brief Handles an error during token expansion.
 *
 * This function sets the shell's exit status to EXIT_FAILURE to indicate
 * that an error occurred during the expansion process. It returns NULL
 * to signal that the expansion was unsuccessful.
 *
 * @param shell A pointer to the shell structure to update the exit status.
 * @return Always returns NULL to indicate an expansion error.
 */

static char	*ft_handle_expansion_error(t_shell *shell)
{
	shell->exit_status = EXIT_FAILURE;
	return (NULL);
}

/**
 * @brief Appends a character to the expanded value string.
 *
 * This function takes a character and appends it to the given expanded
 * value string. The function allocates a new string with the appended
 * character, frees the original expanded value string, and returns the
 * new expanded string.
 *
 * @param expanded_value The current expanded string to which the character
 * will be appended.
 * @param c The character to append to the expanded value string.
 * @return A new string with the character appended, or NULL if memory
 * allocation fails.
 */

char	*ft_process_char(t_shell *shell, char *expanded_value, char c)
{
	char	c_str[2];
	char	*new_expanded;

	c_str[0] = c;
	c_str[1] = '\0';
	new_expanded = ft_safe_strjoin(shell, expanded_value, c_str, 1);
	return (new_expanded);
}
