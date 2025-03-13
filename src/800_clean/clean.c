/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:46:15 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 11:24:34 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	shell->prompt = NULL;
	if (shell->input)
		ft_free(shell->input);
	shell->input = NULL;
	ft_cleanup_tokens(shell);
	ft_cleanup_redirects(shell);
	ft_free(shell->tml);
	shell->tml = NULL;
	close(g_gbl.g_og_stdout);
	ft_close_fds();
}

/**
 * Frees all dynamically allocated memory associated with the shell structure,
 * including the tokens, redirects and prompt strings, and the copy of the
 * environment variables.
 *
 * @param shell The shell structure to free.
 */
void	ft_cleanup_w_env(t_shell *shell)
{
	ft_cleanup(shell);
	if (shell->env_cpy)
		ft_free_arr(shell->env_cpy);
	ft_free(shell->last_cwd);
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
void	ft_cleanup_tokens(t_shell *shell)
{
	t_token	*curr;
	t_token	*next;

	curr = shell->tokens;
	while (curr)
	{
		next = curr->next;
		if (curr->val.og_value)
			ft_free(curr->val.og_value);
		if (curr->val.value)
			ft_free(curr->val.value);
		ft_free(curr);
		curr = next;
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
void	ft_cleanup_redirects(t_shell *shell)
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

/**
 * Frees all dynamically allocated memory associated with the temporary files
 * linked list in the shell structure. This includes the memory allocated for
 * each temporary file's filename string, and the memory allocated for the
 * array of strings itself.
 *
 * @param shell The shell structure containing the temporary files linked list
 *              to free.
 */
void	ft_cleanup_temp_files(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->temp_files)
		return ;
	while (shell->temp_files[i])
	{
		unlink(shell->temp_files[i]);
		ft_free(shell->temp_files[i]);
		i++;
	}
	ft_free(shell->temp_files);
	shell->temp_files = NULL;
}
