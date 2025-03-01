/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:59:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 16:23:58 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_update_shlvl(t_shell *shell);

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
	ft_update_shlvl(shell);
	if (!shell->env_cpy)
		return (ft_print_error(ERR_ENV_DUP_FAIL));
	shell->prompt = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->redirects = NULL;
	shell->temp_files = NULL;
	shell->redirected_stdin = -1;
	shell->redirected_stdout = -1;
	shell->in_export = 0;
	g_exit_status = EXIT_SUCCESS;
	return (SUCCESS);
}

static void	ft_update_shlvl(t_shell *shell)
{
	char	*shlvl;
	char	*res;
	int		shlvl_num;

	shlvl = ft_get_var_value("SHLVL", shell->env_cpy);
	if (shlvl)
	{
		shlvl_num = ft_atoi(shlvl) + 1;
		res = ft_itoa(shlvl_num);
		ft_update_or_add_var("SHLVL", res, shell, 0);
		ft_free(res);
	}
	else
		ft_update_or_add_var("SHLVL", "1", shell, 0);
}
