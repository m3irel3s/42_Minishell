/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:46:15 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 10:24:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Cleans up and frees all allocated resources within the shell structure.
 *
 * This function is responsible for deallocating memory used by the shell's
 * prompt string, input string, and token linked list. It iterates through the
 * tokens linked list and frees each token's value and the token itself.
 * Additionally, it clears the readline history to ensure no residual
 * allocations are left.
 *
 * @param shell A pointer to the shell structure whose resources are to be
 *              cleaned up.
 */
void	ft_cleanup(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	if (shell->prompt)
		free(shell->prompt);
	if (shell->input)
		free(shell->input);
	current = shell->tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	shell->tokens = NULL;
}
