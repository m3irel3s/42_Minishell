/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 08:17:37 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_validate_pipe(t_shell *shell, t_token *current, t_token *prev);
static t_status	ft_validate_redirect(t_shell *shell, t_token *current);

t_status	ft_validate_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!shell || !tokens)
	{
		ft_putstr_fd(ERR_INVALID_PARAMS, STDERR_FILENO);
		if (shell)
			shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	current = tokens;
	prev = tokens->prev;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (ft_validate_pipe(shell, current, prev) != SUCCESS)
				return (ERROR);
		}
		else if (current->type >= REDIRECT_IN && current->type <= HEREDOC)
		{
			if (ft_validate_redirect(shell, current) != SUCCESS)
				return (ERROR);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

static t_status	ft_validate_pipe(t_shell *shell, t_token *current,
		t_token *prev)
{
	if (!prev || prev->type == PIPE || !current->next)
		return (ft_print_syntax_error(shell, "|"));
	return (SUCCESS);
}

static t_status	ft_validate_redirect(t_shell *shell, t_token *current)
{
	if (!current->next)
		return (ft_print_redirect_no_file_error(shell));
	if (current->next->type != WORD)
		return (ft_print_syntax_error(shell, current->next->value));
	if (current->type == HEREDOC && ft_strlen(current->next->value) == 0)
		return (ft_print_heredoc_delim_error(shell));
	return (SUCCESS);
}
