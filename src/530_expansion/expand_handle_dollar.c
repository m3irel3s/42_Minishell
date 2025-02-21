/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:14:30 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 12:35:46 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_exit_status(t_shell *shell, size_t *i);
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
				size_t start);

/**
 * @brief Expands a dollar character ($) in a token into its value.
 *
 * Handles the expansion of a dollar character in a token by calling the
 * appropriate function based on the following character. If the character is a
 * '?', the function ft_expand_exit_status is called. Otherwise,
 * ft_expand_variable is called. If either of the functions fail, the
 * shell->exit_status is set to EXIT_FAILURE.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param token The token containing the dollar character.
 * @param i A pointer to the index of the dollar character in the token.
 * @return The expanded value of the dollar character as a string.
 */
char	*ft_handle_dollar(t_shell *shell, char *token, size_t *i)
{
	char	*res;
	size_t	start;

	if (!shell || !token || !i)
	{
		ft_putstr_fd(ERR_INVALID_PARAMS, STDERR_FILENO);
		if (shell)
			shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
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
	if (!res)
		shell->exit_status = EXIT_FAILURE;
	return (res);
}

/**
 * @brief Converts the shell's exit status to a string.
 *
 * This function increments the index pointer, converts the shell's current
 * exit status into a string using ft_itoa, and returns the result. If memory
 * allocation fails during the conversion, an error message is printed to
 * standard error, and the shell's exit status is set to failure.
 *
 * @param shell A pointer to the shell structure containing the exit status.
 * @param i A pointer to the current position, which will be incremented.
 * @return The exit status as a string, or NULL on failure.
 */

static char	*ft_expand_exit_status(t_shell *shell, size_t *i)
{
	char	*res;

	(*i)++;
	res = ft_itoa(shell->exit_status);
	if (!res)
	{
		ft_putstr_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		shell->exit_status = EXIT_FAILURE;
	}
	return (res);
}

/**
 * @brief Expands a variable from a token, retrieving its value from the
 * environment.
 *
 * This function extracts a variable name starting at a given position within
 * a token, retrieves its value from the shell's environment, and returns the
 * value as a string.
 * If the variable does not exist, an empty string is returned. In case of memory
 * allocation failure, the function sets the shell's exit status to failure and
 * returns NULL.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param token The token containing the variable to be expanded.
 * @param i A pointer to the current position in the token, which will be
 * updated.
 * @param start The starting index of the variable name in the token.
 * @return The expanded variable value as a string, or NULL on failure.
 */

static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
	size_t start)
{
	char	*var_name;
	char	*var_value;
	char	*res;

	var_name = ft_substr(token, start, *i - start);
	if (!var_name)
	{
		ft_putstr_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	var_value = ft_get_var_value(var_name, shell->env_cpy);
	ft_free(var_name);
	if (var_value)
		res = ft_safe_strdup(var_value);
	else
		res = ft_safe_strdup("");
	if (!res)
	{
		ft_putstr_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		shell->exit_status = EXIT_FAILURE;
	}
	return (res);
}
