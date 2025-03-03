/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/01 14:06:34 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	ft_echo_handle_flag(char *str);
static void	ft_echo_print_args(t_token *curr);

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
	ft_echo_print_args(curr);
	if (add_new_line)
		ft_printf(STDOUT_FILENO, "\n");
	g_exit_status = EXIT_SUCCESS;
}

static void	ft_echo_print_args(t_token *curr)
{
	while (curr)
	{
		ft_printf(STDOUT_FILENO, "%s", curr->val.value);
		curr = curr->next;
		if (curr && curr->type == WORD)
			ft_printf(STDOUT_FILENO, " ");
		else
			break ;
	}
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
