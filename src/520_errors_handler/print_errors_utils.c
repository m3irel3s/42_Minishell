/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:30:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 15:30:00 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_format_error(char *err, const char *file)
{
	char	*formatted;
	size_t	total_len;

	if (!err || !file)
		return (NULL);
	total_len = ft_strlen(err) + ft_strlen(file) + 2 + 1;
	formatted = ft_safe_malloc(sizeof(char) * total_len);
	if (!formatted)
		return (NULL);
	formatted[0] = '\0';
	ft_strlcat(formatted, err, total_len);
	ft_strlcat(formatted, ": ", total_len);
	ft_strlcat(formatted, file, total_len);
	return (formatted);
}
