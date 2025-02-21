/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 20:57:51 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Checks if the shell's token list contains any pipe tokens.
 *
 * @param shell Pointer to the shell structure containing the token list.
 * @return t_status Returns SUCCESS if a pipe token is found, ERROR otherwise.
 */
t_status	ft_has_pipes(t_shell *shell)
{
	t_token	*curr;

	if (!shell || !shell->tokens)
		return (ERROR);

	curr = shell->tokens;
	while (curr)
	{
		if (curr->type == PIPE)
			return (SUCCESS);
		curr = curr->next;
	}
	return (ERROR);
}
