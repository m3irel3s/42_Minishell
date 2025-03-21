/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:59:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/16 21:54:17 by meferraz         ###   ########.fr       */
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
	shell->last_cwd = NULL;
	shell->prompt = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->redirects = NULL;
	shell->temp_files = NULL;
	shell->redirected_stdin = -1;
	shell->redirected_stdout = -1;
	shell->are_pipes = 0;
	shell->random_number = 0;
	shell->tml = NULL;
	g_exit_status = EXIT_SUCCESS;
	return (SUCCESS);
}

/**
 * @brief Updates the SHLVL environment variable in the shell.
 *
 * Retrieves the current value of the SHLVL environment variable, increments it
 * by 1, and updates the variable in the shell's environment. If SHLVL does not
 * exist, it initializes it with a value of 1.
 *
 * @param shell A pointer to the shell structure containing the environment.
 */

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

/**
 * @brief Retrieves a pointer to a static shell instance.
 *
 * This function returns a pointer to a static instance of the t_shell
 * structure, which is used to maintain the shell's state throughout
 * the program's execution.
 *
 * @return A pointer to the static t_shell instance.
 */
t_shell	*ft_get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
