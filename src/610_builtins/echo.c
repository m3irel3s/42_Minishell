/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 13:19:15 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_shell *shell)
{
	t_token	*current;
	bool	add_new_line;

	add_new_line = true;
	current = shell->tokens;
	if (!current->next)
		return ;
	if (ft_strncmp(current->next->value, "-n", 3) == SUCCESS)
	{
		add_new_line = false;
		current = current->next;
	}
	while (current->next)
	{
		printf("%s", current->next->value);
		current = current->next;
		if (!current->next)
			break ;
		printf(" ");
	}
	if (add_new_line == true)
		printf("\n");
}
