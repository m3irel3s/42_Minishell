/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:59:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 14:35:12 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * Initializes the given shell structure.
 *
 * @param shell A pointer to the shell structure to be initialized.
 * @param envp An array of environment variables passed to the shell.
 *
 * This function sets the shell's environment pointer to the provided envp
 * array and initializes the prompt and input fields to NULL.
 */
void	ft_init_shell(t_shell *shell, char **envp)
{
	shell->dup_env = ft_duplicate_env(envp);
	shell->prompt = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
}
