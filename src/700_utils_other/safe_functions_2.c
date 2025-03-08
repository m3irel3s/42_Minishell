/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:31:57 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/08 14:54:18 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_strnlen(const char *s, size_t maxlen);

/**
 * @brief Safely duplicates up to n characters of a string.
 *
 * This function duplicates at most `n` characters from the string `s1`
 * into a newly allocated space. It behaves like `strndup`, but if the
 * allocation fails, it returns NULL and an error message is printed.
 *
 * @param s1 The string to duplicate from.
 * @param n The maximum number of characters to duplicate.
 *
 * @return A pointer to the newly allocated string, or NULL if allocation fails.
 */
char	*ft_safe_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strnlen(s1, n);
	copy = ft_safe_calloc(len + 1);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s1, len);
	copy[len] = '\0';
	return (copy);
}

/**
 * @brief Like `strlen`, but only up to `maxlen` characters.
 *
 * This function is like `strlen`, but it will only count up to `maxlen`
 * characters, even if the string is longer. This is useful for avoiding
 * buffer overflows.
 *
 * @param s The string to get the length of.
 * @param maxlen The maximum number of characters to count.
 *
 * @return The length of the string, up to `maxlen`.
 */
static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}
