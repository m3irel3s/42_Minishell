/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:46:15 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/15 17:20:54 by jmeirele         ###   ########.fr       */
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
	t_redirect	*redirect;
	t_redirect	*next_redirect;

	if (shell->prompt)
		free(shell->prompt);
	if (shell->input)
		free(shell->input);
	shell->input = NULL;
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
	redirect = shell->redirects;
	while (redirect)
	{
		next_redirect = redirect->next;
		if (redirect->filename)
			free(redirect->filename);
		free(redirect);
		redirect = next_redirect;
	}
	shell->redirects = NULL;
}

// In a new file or at the end of an existing utility file
void ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void ft_free_token(t_token *token)
{
	if (token)
	{
		ft_free(token->value);
		ft_free(token);
	}
}

void ft_free_arr(char **arr)
{
	int i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

