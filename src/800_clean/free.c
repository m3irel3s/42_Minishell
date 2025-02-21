/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:17:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 09:02:52 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * Frees the memory allocated at the given pointer.
 *
 * @param ptr The pointer to the memory to be freed. If the pointer is NULL,
 *            the function does nothing.
 */

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

/**
 * Frees the memory allocated for a token, including its value.
 *
 * This function releases the memory used by the token's value and the
 * token itself. If the token is NULL, the function does nothing.
 *
 * @param token The token to be freed.
 */

void	ft_free_token(t_token *token)
{
	if (token)
	{
		ft_free(token->value);
		ft_free(token);
	}
}

/**
 * Frees the memory allocated for an array of strings.
 *
 * This function iterates through the array of strings, freeing each
 * individual string and then frees the array itself. If the array is
 * NULL, the function does nothing.
 *
 * @param arr The array of strings to be freed.
 */

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}
