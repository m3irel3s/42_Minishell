/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 10:36:18 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_status	ft_expand(t_shell *shell)
{
	t_token *current;
	char *expanded_value;

	current = shell->tokens;
	while (current)
	{
		expanded_value = ft_expand_token(shell, current->value);
		if (!expanded_value)
			return (ERROR);
		free(current->value);
		current->value = expanded_value;
		current = current->next;
	}
	return (SUCCESS);
}
