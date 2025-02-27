/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:31:57 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_safe_realloc(void *old_ptr, size_t new_size)
{
	char	*new_ptr;
	char	*old_char;
	size_t	old_len;
	size_t	i;

	if (!old_ptr)
		return (ft_safe_malloc(new_size));
	old_char = (char *)old_ptr;
	old_len = 0;
	while (old_char[old_len])
		old_len++;
	new_ptr = ft_safe_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < old_len && i < new_size - 1)
	{
		new_ptr[i] = old_char[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(old_ptr);
	return ((void *)new_ptr);
}
#include <stddef.h>

size_t ft_strnlen(const char *s, size_t maxlen)
{
	size_t len = 0;

	while (len < maxlen && s[len] != '\0')
	{
		len++;
	}

	return len;
}

char *ft_safe_strndup(const char *s1, size_t n)
{
	char *copy;
	size_t len;

	if (!s1)
		return NULL;

	len = ft_strnlen(s1, n);
	copy = ft_safe_malloc(len + 1);
	if (!copy)
		return NULL;

	ft_memcpy(copy, s1, len);
	copy[len] = '\0';

	return copy;
}
