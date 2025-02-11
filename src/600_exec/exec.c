/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 15:57:43 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute_input(t_shell *shell)
{
	if (shell->tokens == NULL)
		return ;
	else if (ft_strncmp(shell->tokens->value, "echo", 5) == SUCCESS)
		ft_echo(shell);
	else if (ft_strncmp(shell->tokens->value, "cd", 3) == SUCCESS)
		ft_cd(shell);
	else if (ft_strncmp(shell->tokens->value, "env", 4) == SUCCESS)
		ft_env(shell);
	else if (ft_strncmp(shell->tokens->value, "pwd", 4) == SUCCESS)
		ft_pwd(shell);
	// else if (ft_strncmp(shell->tokens->value, "export", 7) == SUCCESS)
	// 	ft_export(shell);
	return ;
}
