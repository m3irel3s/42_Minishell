/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 12:45:52 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_shell *shell)
{
	t_token	*curr;
	bool	add_new_line;

	add_new_line = true;
	curr = shell->tokens;
	if (!curr->next)
		return ;
	if (ft_strncmp(curr->next->value, "-n", 3) == SUCCESS)
	{
		add_new_line = false;
		curr = curr->next;
	}
	while (curr->next)
	{
		ft_printf(1, "%s", curr->next->value);
		curr = curr->next;
		if (!curr->next)
			break ;
		ft_printf(1, " ");
	}
	if (add_new_line == true)
		ft_printf(1, "\n");
}
