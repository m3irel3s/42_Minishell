/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 10:19:00 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute_input(t_shell *shell)
{
	if (ft_strncmp(shell->tokens->value, "echo", 5) == SUCCESS)
		ft_echo(shell);
	if (ft_strncmp(shell->tokens->value, "cd", 3) == SUCCESS)
		ft_cd(shell);
	if (ft_strncmp(shell->tokens->value, "env", 3) == SUCCESS)
		ft_env(shell);
	return ;
}