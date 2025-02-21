/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 13:50:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Allocates memory for an object of the given size.
 *
 * @param size The size of the object to allocate in bytes.
 * @return A pointer to the allocated memory if the allocation was successful,
 *         otherwise the program will exit with an error message.
 *
 * @note This function does not check if the allocation size is valid
 *       (i.e. not zero). It is the caller's responsibility to ensure the size
 *       is valid before calling this function.
 */
void	*ft_safe_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
	{
		write(2, "Error: Invalid allocation size <= 0.\n", 37);
		exit(EXIT_FAILURE);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Error: Memory allocation failed.\n", 33);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * Reads a line of input from the user using readline(3) safely.
 *
 * @param shell A pointer to the shell's internal state.
 * @return A pointer to the input string if the read was successful, otherwise
 *         the program will exit with an error message.
 *
 * @note This function will clean up the shell's internal state and exit the
 *       program if the read fails. It is the caller's responsibility to ensure
 *       the shell's prompt is valid before calling this function.
 */
char	*ft_safe_readline(t_shell *shell)
{
	char	*input;

	if (!shell->prompt)
	{
		write(2, "minishell: invalid prompt\n", 26);
		return (NULL);
	}
	input = readline(shell->prompt);
	return (input);
}

/**
 * @brief Safely duplicates a string.
 *
 * Allocates memory for a duplicate of the input string and copies its
 * contents into the newly allocated memory. If memory allocation fails,
 * the program exits with an error message.
 *
 * @param s The string to be duplicated.
 *
 * @return A pointer to the newly duplicated string or NULL if the input
 *         string is NULL.
 */

char	*ft_safe_strdup(char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = ft_safe_malloc(len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}

/**
 * @brief A safe version of ft_strjoin that handles errors and frees the first
 * string if requested.
 *
 * This function is similar to ft_strjoin, but it checks for errors and frees
 * the first string if requested. If the memory allocation fails, it sets the
 * shell's exit status to EXIT_FAILURE and returns NULL.
 *
 * @param shell The shell structure.
 * @param s1 The first string to join.
 * @param s2 The second string to join.
 * @param free_s1 A flag indicating whether to free the first string.
 * @return The joined string, or NULL if there was an error.
 */
char	*ft_safe_strjoin(t_shell *shell, char *s1, char *s2, int free_s1)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_s1)
	{
		if (s1)
			ft_free(s1);
	}
	if (!result)
		return (ft_handle_error(shell, ERR_STRJOIN_FAIL));
	return (result);
}
