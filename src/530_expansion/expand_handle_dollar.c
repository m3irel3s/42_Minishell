/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:14:30 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/01 15:14:45 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_expand_exit_status(size_t *i);
static char	*ft_expand_number(char *token, size_t *i);
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
				size_t start);
static char	*ft_set_error_and_return_null(void);

/**
 * @brief Expands a special variable starting with "$".
 *
 * This function takes a pointer to the shell structure, a string token, and a
 * pointer to the current index of the token string. It expands the special
 * variable starting with "$" and returns the expanded value as a string.
 *
 * The function supports two special variables: "$?" and any variable name
 * starting with "$" followed by alphanumeric characters or "_". The "$?"
 * special variable is expanded to the exit status of the last command executed
 * in the shell, and any other variable name is expanded to the value of the
 * corresponding environment variable.
 *
 * The function returns NULL and sets the shell's exit status to failure if
 * memory allocation fails.
 *
 * @param shell A pointer to the shell structure.
 * @param token The token string containing the special variable to be expanded.
 * @param i A pointer to the current index of the token string.
 * @return The expanded value of the special variable as a string, or NULL if
 * memory allocation fails.
 */
char	*ft_handle_dollar(t_shell *shell, char *token, size_t *i)
{
	char	*res;
	size_t	start;

	if (!shell || !token || !i)
	{
		ft_print_error(ERR_INVALID_PARAMS);
		return (NULL);
	}
	res = NULL;
	(*i)++;
	if (token[*i] == '?')
		res = ft_expand_exit_status(i);
	else if (ft_isdigit(token[*i]))
		res = ft_expand_number(token, i);
	else
	{
		start = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			(*i)++;
		res = ft_expand_variable(shell, token, i, start);
	}
	if (!res)
		return (ft_set_error_and_return_null());
	return (res);
}

/**
 * @brief Expands a number found in the token string.
 *
 * This function expands a sequence of digits in the token string to the
 * corresponding string value. The start index of the sequence is given by
 * the value of \p i, and the end index is determined by finding the next
 * non-digit character. If memory allocation fails, the function sets the
 * shell's exit status to failure and returns NULL.
 *
 * @param shell A pointer to the shell structure.
 * @param token The token string containing the number to be expanded.
 * @param i A pointer to the current index of the token string.
 * @return The expanded value of the number as a string, or NULL if memory
 * allocation fails.
 */
static char	*ft_expand_number(char *token, size_t *i)
{
	char	*res;
	size_t	start;

	(*i)++;
	start = *i;
	if (ft_isalnum(token[*i]))
		(*i)++;
	res = ft_safe_substr(token, start, *i - start);
	if (!res)
		return (ft_set_error_and_return_null());
	return (res);
}
/**
 * @brief Expands the "$?" special variable.
 *
 * This function returns a string containing the exit status of the last
 * command executed in the shell. The exit status is retrieved from the shell's
 * exit_status field and converted to a string using ft_itoa.
 *
 * @param shell A pointer to the shell structure containing the exit_status
 * field.
 * @param i A pointer to the current index of the token string.
 * @return A string containing the exit status of the last command, or NULL if
 * memory allocation fails.
 */

static char	*ft_expand_exit_status(size_t *i)
{
	char	*res;

	(*i)++;
	res = ft_itoa(g_exit_status);
	if (!res)
		return (ft_set_error_and_return_null());
	return (res);
}

/**
 * @brief Expands a variable from the shell's environment.
 *
 * This function takes a substring of the token, starting from the position
 * where the '$' character was found, and up to the current index, and uses
 * it as a variable name. It then looks up the variable's value in the
 * shell's environment, and returns a copy of that value. If the variable is
 * not found, an empty string is returned. If memory allocation fails, the
 * function sets the shell's exit status to failure and returns NULL.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param token The token containing the variable name.
 * @param i A pointer to the current index in the token.
 * @param start The starting position of the substring.
 * @return A copy of the variable's value, or an empty string if not found,
 * or NULL if there is a memory allocation failure.
 */
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
	size_t start)
{
	char	*var_name;
	char	*var_value;
	char	*res;

	var_name = ft_safe_substr(token, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = ft_get_var_value(var_name, shell->env_cpy);
	ft_free(var_name);
	if (var_value)
		res = ft_safe_strdup(var_value);
	else
		res = ft_safe_strdup("");
	if (!res)
		return (ft_set_error_and_return_null());
	return (res);
}

/**
 * @brief Handles an error during variable expansion by setting the shell's
 * exit status to failure and returning NULL.
 *
 * @param shell A pointer to the shell structure containing environment info.
 *
 * @return NULL to indicate that an error occurred.
 */
static char	*ft_set_error_and_return_null(void)
{
	g_exit_status = EXIT_FAILURE;
	return (NULL);
}
