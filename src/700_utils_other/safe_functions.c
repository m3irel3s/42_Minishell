/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/11 15:37:04 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Allocates memory safely and handles errors.
 *
 * This function attempts to allocate the specified amount of memory. If the
 * requested size is invalid (i.e., less than or equal to zero), an error
 * message is printed, the shell's exit status is set to EXIT_FAILURE, and
 * NULL is returned. If the memory allocation fails, an error message is
 * printed, the shell's exit status is set to EXIT_FAILURE, and NULL is
 * returned.
 *
 * @param shell A pointer to the shell structure to store error state.
 * @param size The size of memory to allocate.
 *
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_safe_calloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
	{
		ft_print_error(ERR_INVALID_ALLOC_SIZE);
		g_gbl.g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	ptr = ft_calloc(1, size);
	if (!ptr)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		g_gbl.g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	return (ptr);
}

/**
 * @brief Safely reads a line of input from the user using the shell's prompt.
 *
 * This function uses the readline library to read a line of input from the user,
 * prompted by the shell's current prompt string. If the shell's prompt is NULL,
 * an error message is printed, the shell's exit status is set to EXIT_FAILURE,
 * and NULL is returned.
 *
 * @param shell A pointer to the shell structure containing the prompt
 * information.
 *
 *
 * @return A dynamically allocated string containing the user's input, or NULL
 * if the shell's prompt is invalid.
 */

char	*ft_safe_readline(t_shell *shell)
{
	char	*input;

	if (!shell->prompt)
	{
		ft_print_error(ERR_INVALID_PROMPT);
		g_gbl.g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	input = readline(shell->prompt);
	return (input);
}

/**
 * @brief A safe version of the ft_strdup function.
 *
 * This function is identical to ft_strdup, but it will print an error message
 * and set the shell's exit status to EXIT_FAILURE if the memory
 * allocation fails.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param s The string to be duplicated.
 *
 * @return The duplicated string, or NULL if the memory allocation fails.
 */
char	*ft_safe_strdup(char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
	{
		g_gbl.g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	len = ft_strlen(s) + 1;
	dup = ft_safe_calloc(len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}

/**
 * @brief A safe version of the ft_strjoin function.
 *
 * This function is identical to ft_strjoin, but it will print an error
 * message and set the shell's exit status to EXIT_FAILURE if the
 * memory allocation fails.
 *
 * @param shell A pointer to the shell structure containing environment info.
 * @param s1 The first string to be joined.
 * @param s2 The second string to be joined.
 * @param free_s1 If true, the function will free s1 after the join.
 *
 * @return The joined string, or NULL if the memory allocation fails.
 */
char	*ft_safe_strjoin(char *s1, char *s2, int free_s1)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_s1 && s1)
		ft_free(s1);
	if (!result)
	{
		ft_print_error(ERR_STRJOIN_FAIL);
		g_gbl.g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	return (result);
}

/**
 * Safely allocates a substring from the given string `s` and returns it.
 * The substring will start at index `start` and will have a maximum
 * length of `len`.
 * If `start` is greater than or equal to the length of `s`, an empty string
 * is returned.
 * If `len` is greater than the number of remaining characters in `s`, the
 * substring will
 * be truncated to the remaining characters.
 * If there is an error allocating the substring, an error message is printed and
 * `NULL` is returned.
 */
char	*ft_safe_substr(char *s, int start, int len)
{
	char	*substr;
	int		s_len;

	if (!s)
	{
		ft_print_error(ERR_INVALID_PARAMS);
		g_gbl.g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_safe_strdup(""));
	if (len == 0)
		return (ft_safe_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)ft_safe_calloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
