/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:46:15 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 12:20:56 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

static void	ft_cleanup_tokens(t_shell *shell);
static void	ft_cleanup_redirects(t_shell *shell);

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
