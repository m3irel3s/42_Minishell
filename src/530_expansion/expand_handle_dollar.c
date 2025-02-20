/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:14:30 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 15:11:46 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_exit_status(t_shell *shell, size_t *i);
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
				size_t start);
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
				size_t start);

/**
 * @brief Handles dollar sign expansion in a token.
 *
 * This function processes a token starting with a dollar sign ('$') at the
 * current index, expanding either the exit status if followed by '?' or a
 * variable name otherwise. The index is updated to point after the processed
 * part of the token.
 *
 * @param shell The shell struct containing the environment and state
 * information.
 * @param token The input string token being processed.
 * @param i Pointer to the current index in the token string.
 * @return A string representing the expanded value, or NULL if no expansion
 *         was possible.
 */

char	*ft_handle_dollar(t_shell *shell, char *token, size_t *i)
{
	char	*res;
	size_t	start;

	res = NULL;
	(*i)++;
	if (token[*i] == '?')
		res = ft_expand_exit_status(shell, i);
	else
	{
		start = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			(*i)++;
		res = ft_expand_variable(shell, token, i, start);
	}
	return (res);
}

/**
 * @brief Expands the exit status variable in the shell.
 *
 * This function increments the index to skip the '?' character
 * and converts the shell's exit status to a string.
 *
 * @param shell The shell struct containing the exit status.
 * @param i Pointer to the current index in the token string.
 * @return A string representing the exit status.
 */

static char	*ft_expand_exit_status(t_shell *shell, size_t *i)
{
	char	*res;

	(*i)++;
	res = ft_itoa(shell->exit_status);
	return (res);
}

/**
 * @brief Expands a variable in the shell.
 *
 * This function extracts the variable name from the token, gets its value from
 * the environment and returns it as a string. If the variable doesn't exist,
 * it returns an empty string.
 *
 * @param shell The shell struct containing the environment and state
 * information.
 * @param token The input string token being processed.
 * @param i Pointer to the current index in the token string.
 * @param start The start index of the variable name in the token string.
 * @return A string representing the expanded variable value.
 */
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
	size_t start)
{
	char	*var_name;
	char	*var_value;
	char	*res;

	var_name = ft_substr(token, start, *i - start);
	if (!var_name)
		return (ft_strdup("$"));
	var_value = ft_get_var_value(var_name, shell->env_cpy);
	ft_free(var_name);
	if (var_value)
		res = ft_strdup_safe(var_value);
	else
		res = ft_strdup("");
	return (res);
}
