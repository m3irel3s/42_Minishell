/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:59 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 14:39:31 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static int	ft_handle_cd_home(t_shell *shell, char *curr_path);
static int	ft_handle_cd_oldpwd(t_shell *shell, char *curr_path);
static int	ft_handle_cd_to_dir(t_shell *shell, t_token *curr, char *curr_path);
static int	ft_update_pwd(t_shell *shell, char *old_path);

void	ft_cd(t_shell *shell)
{
	t_token	*curr;
	char	*curr_path;

	curr = shell->tokens;
	curr_path = ft_get_current_directory();
	if (!curr_path)
	{
		ft_print_error(ERR_GET_CWD_FAIL);
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	if (!curr->next || ft_strncmp(curr->next->value, "~", 2) == SUCCESS)
		g_exit_status = ft_handle_cd_home(shell, curr_path);
	else if (ft_strncmp(curr->next->value, "-", 2) == SUCCESS)
		g_exit_status = ft_handle_cd_oldpwd(shell, curr_path);
	else
		g_exit_status = ft_handle_cd_to_dir(shell, curr, curr_path);
	ft_free(curr_path);
}

static int	ft_handle_cd_home(t_shell *shell, char *curr_path)
{
	char	*home_path;

	home_path = ft_get_var_value("HOME", shell->env_cpy);
	if (ft_strcmp(home_path, "") == SUCCESS)
	{
		ft_print_error_w_arg(ERR_HOME_NOT_SET, "HOME");
		return (EXIT_FAILURE);
	}
	if (chdir(home_path) != 0)
	{
		ft_print_error_w_arg(ERR_CD_FAIL, home_path);
		return (EXIT_FAILURE);
	}
	return (ft_update_pwd(shell, curr_path));
}

static int	ft_handle_cd_oldpwd(t_shell *shell, char *curr_path)
{
	char	*old_pwd;

	old_pwd = ft_get_var_value("OLDPWD", shell->env_cpy);
	if (!old_pwd)
	{
		ft_print_error(ERR_OLDPWD_NOT_SET);
		return (EXIT_FAILURE);
	}
	if (chdir(old_pwd) != 0)
	{
		ft_print_error(ERR_OLDPWD_NOT_SET);
		return (EXIT_FAILURE);
	}
	ft_printf(STDOUT_FILENO, "%s\n", old_pwd);
	return (ft_update_pwd(shell, curr_path));
}

static int	ft_handle_cd_to_dir(t_shell *shell, t_token *curr, char *curr_path)
{
	char	*path;

	path = curr->next->value;
	if (chdir(path) != 0)
	{
		ft_print_error_w_arg(ERR_CD_FAIL, path);
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
		ft_print_error(ERR_GET_CWD_FAIL);
		return (EXIT_FAILURE);
	}
	ft_update_or_add_var("OLDPWD", old_path, shell, 0);
	ft_update_or_add_var("PWD", new_path, shell, 0);
	ft_free(new_path);
	return (EXIT_SUCCESS);
}
