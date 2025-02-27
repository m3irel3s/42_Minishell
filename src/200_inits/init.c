/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:59:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 13:41:30 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Initializes the given shell structure.
 *
 * @param shell A pointer to the shell structure to be initialized.
 * @param envp An array of environment variables passed to the shell.
 *
 * @return SUCCESS if initialization is successful, ERROR otherwise.
 */
t_status	ft_init_shell(t_shell *shell, char **envp)
{
	shell->env_cpy = ft_duplicate_env(envp);
	if (!shell->env_cpy)
		return (ft_print_error(ERR_ENV_DUP_FAIL));
	shell->prompt = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->redirects = NULL;
	shell->redirected_stdin = -1;
	shell->redirected_stdout = -1;
	shell->in_export = 0;
	g_exit_status = EXIT_SUCCESS;
	return (SUCCESS);
}
