/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:26:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/16 22:26:17 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_handle_cd_home(t_shell *shell, char *curr_path);
static int	ft_handle_cd_oldpwd(t_shell *shell, char *curr_path);
static int	ft_handle_cd_to_dir(t_shell *shell, t_token *curr, char *curr_path);
static int	ft_update_pwd(t_shell *shell, char *old_path);

/**
 * @brief Changes the current directory to the one provided in the arguments.
 * If no argument is given, changes to the home directory. If the argument is
 * "-", changes to the old working directory.
 *
 * @param shell a pointer to the struct containing the shell's information.
 */
void	ft_cd(t_shell *shell)
{
	t_token	*curr;
	char	*curr_path;

	if (!shell)
		return ;
	curr = shell->tokens;
	curr_path = ft_get_current_directory();
	if (!curr_path)
	{
		if (shell->last_cwd)
			curr_path = ft_strdup(shell->last_cwd);
		if (!curr_path)
		{
			ft_print_error(ERR_GET_CWD_FAIL);
			g_exit_status = EXIT_FAILURE;
			return ;
		}
	}
	if (!curr->next || ft_strncmp(curr->next->val.value, "~", 2) == SUCCESS)
		g_exit_status = ft_handle_cd_home(shell, curr_path);
	else if (ft_strncmp(curr->next->val.value, "-", 2) == SUCCESS)
		g_exit_status = ft_handle_cd_oldpwd(shell, curr_path);
	else
		g_exit_status = ft_handle_cd_to_dir(shell, curr, curr_path);
	ft_free(curr_path);
}

/**
 * @brief Changes the current directory to the home directory.
 *
 * If the home directory is not set, prints an error message and sets the
 * exit status to EXIT_FAILURE. If the change directory operation fails,
 * prints an error message and sets the exit status to EXIT_FAILURE.
 *
 * @param shell a pointer to the struct containing the shell's information.
 * @param curr_path the current working directory.
 * @return EXIT_SUCCESS if the change directory operation was successful,
 * EXIT_FAILURE otherwise.
 */
static int	ft_handle_cd_home(t_shell *shell, char *curr_path)
{
	char	*home_path;

	home_path = ft_get_var_value("HOME", shell->env_cpy);
	if (ft_strcmp(home_path, "") == SUCCESS)
	{
		ft_print_error_w_arg(ERR_HOME_NOT_SET, "HOME", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (chdir(home_path) != 0)
	{
		ft_print_error_w_arg(ERR_CD_FAIL, home_path, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (ft_update_pwd(shell, curr_path));
}

/**
 * @brief Changes the current directory to the old working directory.
 *
 * If the old working directory is not set, prints an error message and sets
 * the exit status to EXIT_FAILURE. If the change directory operation fails,
 * prints an error message and sets the exit status to EXIT_FAILURE.
 *
 * @param shell a pointer to the struct containing the shell's information.
 * @param curr_path the current working directory.
 * @return EXIT_SUCCESS if the change directory operation was successful,
 * EXIT_FAILURE otherwise.
 */
static int	ft_handle_cd_oldpwd(t_shell *shell, char *curr_path)
{
	char	*old_pwd;

	old_pwd = ft_get_var_value("OLDPWD", shell->env_cpy);
	if (ft_strcmp(old_pwd, "") == 0)
	{
		ft_print_error(ERR_OLDPWD_NOT_SET);
		return (EXIT_FAILURE);
	}
	else if (chdir(old_pwd) != 0)
	{
		ft_print_error_w_arg(ERR_CD_FAIL, old_pwd, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	ft_printf(STDOUT_FILENO, "%s\n", old_pwd);
	return (ft_update_pwd(shell, curr_path));
}

/**
 * @brief Changes the current directory to the one specified in the argument.
 * If the argument starts with a tilde, the home directory is prepended to it.
 * If the change directory operation fails, prints an error message and sets
 * the exit status to EXIT_FAILURE.
 *
 * @param shell a pointer to the struct containing the shell's information.
 * @param curr a pointer to the token containing the argument.
 * @param curr_path the current working directory.
 * @return EXIT_SUCCESS if the change directory operation was successful,
 * EXIT_FAILURE otherwise.
 */
static int	ft_handle_cd_to_dir(t_shell *shell, t_token *curr, char *curr_path)
{
	char	*path;

	path = curr->next->val.value;
	if (chdir(path) != 0)
	{
		ft_print_error_w_arg(ERR_CD_FAIL, path, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (ft_update_pwd(shell, curr_path));
}

static int	ft_update_pwd(t_shell *shell, char *old_path)
{
	char	*new_path;

	new_path = ft_get_current_directory();
	if (!new_path)
	{
		if (shell->last_cwd)
			new_path = ft_strdup(shell->last_cwd);
		if (!new_path)
		{
			ft_print_error(ERR_GET_CWD_FAIL);
			return (EXIT_FAILURE);
		}
	}
	ft_update_or_add_var("OLDPWD", old_path, shell, 0);
	ft_update_or_add_var("PWD", new_path, shell, 0);
	if (shell->last_cwd)
		ft_free(shell->last_cwd);
	shell->last_cwd = ft_strdup(new_path);
	ft_free(new_path);
	return (EXIT_SUCCESS);
}
