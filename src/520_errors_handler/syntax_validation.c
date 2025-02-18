/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 11:48:48 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_status	ft_validate_syntax(t_token *tokens)
{
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
