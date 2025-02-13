/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 11:52:25 by jmeirele         ###   ########.fr       */
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
		printf("%s", curr->next->value);
		curr = curr->next;
		if (!curr->next)
			break ;
		printf(" ");
	}
	if (add_new_line == true)
		printf("\n");
}
