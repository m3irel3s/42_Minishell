/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/31 13:29:00 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Error: Memory allocation failed.\n", 33);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * Allocates memory for an array of elements, each of them initialized to zero.
 *
 * @param count The number of elements to allocate.
 * @param size The size of each element in bytes.
 * @return A pointer to the allocated memory if the allocation was successful,
 *         otherwise the program will exit with an error message.
 *
 * @note This function does not check if the total allocation size (count * size)
 *       is valid (i.e. not zero or overflowed). It is the caller's 
 *       responsibility to ensure the sizes are valid before calling 
 *       this function.
 */

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = calloc(count, size);
	if (!ptr)
	{
		write(2, "Error: Memory allocation failed.\n", 33);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

char	*ft_safe_readline(char *prompt)
{
	char	*input;

	if (!prompt)
	{
		write(2, "minishell: invalid prompt\n", 26);
		return (NULL);
	}
	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	return (input);
}
