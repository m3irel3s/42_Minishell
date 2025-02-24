/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:31:57 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/24 10:32:31 by meferraz         ###   ########.fr       */
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
