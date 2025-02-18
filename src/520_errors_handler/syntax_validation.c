/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 11:45:30 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_status	ft_validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = tokens->prev;
	if (current->type == PIPE)
	{
		if (!prev || prev->type == PIPE || !current->next)
			return (ft_print_syntax_error("|"));
	}
	else if (current->type >= REDIRECT_IN && current->type <= HEREDOC)
	{
		if (!current->next)
			return (ft_print_redirect_no_file_error());
		if (current->next->type != WORD)
			return (ft_print_syntax_error(current->next->value));
		if (current->type == HEREDOC && ft_strlen(current->next->value) == 0)
			return (ft_print_heredoc_delim_error());
	}
	return (SUCCESS);
}
