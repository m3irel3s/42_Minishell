/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 16:57:47 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static bool	ft_echo_handle_flag(char *str);

void	ft_echo(t_shell *shell)
{
	t_token	*curr;
	bool	add_new_line;

	add_new_line = true;
	curr = shell->tokens->next;
	if (!curr)
	{
		ft_printf(STDOUT_FILENO, "\n");
		g_exit_status = EXIT_SUCCESS;
		return ;
	}
	while (curr && ft_echo_handle_flag(curr->val.value))
	{
		add_new_line = false;
		curr = curr->next;
	}
	while (curr)
	{
		ft_printf(STDOUT_FILENO, "%s", curr->val.value);
		curr = curr->next;
		if (curr)
			ft_printf(STDOUT_FILENO, " ");
	}
	if (add_new_line)
		ft_printf(STDOUT_FILENO, "\n");
	g_exit_status = EXIT_SUCCESS;
}

static bool	ft_echo_handle_flag(char *str)
{
	int		i;

	i = 0;
	if (str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}
