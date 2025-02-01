/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/01 09:51:16 by meferraz         ###   ########.fr       */
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
	if (!input)
		return (NULL);
	return (input);
}
