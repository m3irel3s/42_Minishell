/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 14:20:10 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Allocate memory safely.
 *
 * This function calls malloc and checks for errors. If there is an error, it
 * will print an error message and exit the program.
 *
 * @param size The amount of memory to allocate.
 * @return A void pointer to the beginning of the allocated memory.
 */
void	*ft_safe_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
	{
		ft_print_error(NULL, ERR_INVALID_ALLOC_SIZE);
		exit(EXIT_FAILURE);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		ft_print_error(NULL, ERR_MALLOC_FAIL);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * Reads a line of input from the user safely.
 *
 * This function checks if the prompt is not NULL and prints an error if it is.
 * It then reads a line of input using readline and returns it as a string.
 *
 * @param shell A pointer to the shell structure containing the prompt.
 * @return The input line as a string, or NULL if there was an error.
 */
char	*ft_safe_readline(t_shell *shell)
{
	char	*input;

	if (!shell->prompt)
	{
		ft_print_error(shell, ERR_INVALID_PROMPT);
		return (NULL);
	}
	input = readline(shell->prompt);
	return (input);
}

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
 * Joins two strings together safely.
 *
 * This function joins two strings together using ft_strjoin and checks for
 * errors. If there is an error, it prints an error message and returns NULL.
 *
 * If free_s1 is set to a non-zero value, the first string is freed after the
 * join operation.
 *
 * @param shell A pointer to the shell structure.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param free_s1 Whether to free the first string after the join.
 * @return The joined string, or NULL if there was an error.
 */
char	*ft_safe_strjoin(t_shell *shell, char *s1, char *s2, int free_s1)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_s1 && s1)
		ft_free(s1);
	if (!result)
		return (ft_print_error(shell, ERR_STRJOIN_FAIL), NULL);
	return (result);
}
