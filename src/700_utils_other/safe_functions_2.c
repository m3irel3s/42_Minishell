/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:31:57 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/01 14:54:33 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_strnlen(const char *s, size_t maxlen);

char	*ft_safe_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strnlen(s1, n);
	copy = ft_safe_malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s1, len);
	copy[len] = '\0';
	return (copy);
}

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}
