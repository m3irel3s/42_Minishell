/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 08:31:50 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_status	ft_validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!prev)
				return (ft_print_syntax_error("|"));
			if (!current->next)
				return (ft_print_syntax_error("newline"));
			if (prev->type == PIPE)
				return (ft_print_syntax_error("|"));
		}
		else if (current->type >= REDIRECT_IN && current->type <= HEREDOC)
		{
			if (!current->next)
				return (ft_print_redirect_no_file_error());
			if (current->next->type != WORD)
				return (ft_print_syntax_error(current->next->value));
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

t_status	ft_print_unmatched_quote_error(void)
{
	ft_putstr_fd(ERR_UNMATCHED_QUOTE, 2);
	return (ERROR);
}

t_status	ft_print_syntax_error(char *token)
{
	ft_printf_fd(2, ERR_UNEXPECTED_TOKEN, token);
	return (ERROR);
}

t_status	ft_print_redirect_no_file_error(void)
{
	ft_putstr_fd(ERR_REDIRECT_NO_FILE, 2);
	return (ERROR);
}
