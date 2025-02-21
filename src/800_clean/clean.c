/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:46:15 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 09:04:46 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_cleanup_tokens(t_shell *shell);
static void	ft_cleanup_redirects(t_shell *shell);

/**
 * Frees all dynamically allocated memory in the shell structure.
 *
 * This includes the prompt string, the input string, the tokens linked list,
 * and the redirects linked list.
 *
 * @param shell The shell structure to free.
 */
void	ft_cleanup(t_shell *shell)
{
	if (shell->prompt)
		ft_free(shell->prompt);
	if (shell->input)
		ft_free(shell->input);
	shell->input = NULL;
	ft_cleanup_tokens(shell);
	ft_cleanup_redirects(shell);
}

/**
 * Frees all dynamically allocated memory associated with the tokens linked
 * list in the shell structure.
 *
 * This includes the memory allocated for each token's value string, and the
 * memory allocated for each token structure itself.
 *
 * @param shell The shell structure containing the tokens linked list to free.
 */
static void	ft_cleanup_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			ft_free(current->value);
		ft_free(current);
		current = next;
	}
	shell->tokens = NULL;
}

/**
 * Frees all dynamically allocated memory associated with the redirects linked
 * list in the shell structure.
 *
 * This includes the memory allocated for each redirect's filename string, and
 * the memory allocated for each redirect structure itself.
 *
 * @param shell The shell structure containing the redirects linked list to free.
 */
static void	ft_cleanup_redirects(t_shell *shell)
{
	t_redirect	*redirect;
	t_redirect	*next_redirect;

	redirect = shell->redirects;
	while (redirect)
	{
		next_redirect = redirect->next;
		if (redirect->filename)
			ft_free(redirect->filename);
		ft_free(redirect);
		redirect = next_redirect;
	}
	shell->redirects = NULL;
}
