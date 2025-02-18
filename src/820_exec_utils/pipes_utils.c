/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 12:46:34 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_has_pipes(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr)
	{
		if (curr->type == PIPE)
			return SUCCESS;
		curr = curr->next;
	}
	return ERROR;
}
