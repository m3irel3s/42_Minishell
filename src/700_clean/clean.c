/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:46:15 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/03 15:42:32 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * Frees dynamically allocated memory and clears the readline history.
 *
 * @param shell A pointer to the shell structure containing the memory to be
 *              freed.
 */
void	ft_cleanup(t_shell *shell)
{
	t_token *current;
	t_token *next;

	current = shell->tokens;
	if (shell->prompt)
		free(shell->prompt);
	if (shell->input)
		free(shell->input);
	if (current)
	{
		while(current)
		{
			next = current->next;
			free(current->value);
			free(current);
			current = next;
		}
		shell->tokens = NULL;
	}
	rl_clear_history();
}
