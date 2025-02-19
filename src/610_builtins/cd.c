/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:59 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 12:45:53 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handle_cd_home(t_shell *shell, t_token *curr, char *curr_path);
static void	ft_handle_cd_oldpwd(t_shell *shell, char *curr_path);
static void	ft_handle_cd_to_dir(t_shell *shell, t_token *curr, char *curr_path);

void	ft_cd(t_shell *shell)
{
	t_token	*curr;
	char	*curr_path;

	curr = shell->tokens;
	curr_path = ft_get_current_directory();
	if (!curr->next || ft_strncmp(curr->next->value, "~", 2) == SUCCESS)
		ft_handle_cd_home(shell, curr, curr_path);
	else if (ft_strncmp(curr->next->value, "-", 2) == SUCCESS)
		ft_handle_cd_oldpwd(shell, curr_path);
	else
		ft_handle_cd_to_dir(shell, curr, curr_path);
	ft_free(curr_path);
}

static void	ft_handle_cd_home(t_shell *shell, t_token *curr, char *curr_path)
{
	char	*new_path;

	if (!curr->next || ft_strncmp(curr->next->value, "~", 2) == SUCCESS)
	{
		ft_update_or_add_var("OLDPWD", curr_path, shell);
		chdir(ft_get_var_value("HOME", shell->env_cpy));
		new_path = ft_get_current_directory();
		ft_update_or_add_var("PWD", new_path, shell);
		ft_free(new_path);
	}
}

static void	ft_handle_cd_oldpwd(t_shell *shell, char *curr_path)
{
	char	*old_pwd;
	char	*new_path;

	old_pwd = ft_get_var_value("OLDPWD", shell->env_cpy);
	if (old_pwd)
	{
		chdir(old_pwd);
		ft_printf(1, "%s\n", old_pwd);
		ft_update_or_add_var("OLDPWD", curr_path, shell);
		new_path = ft_get_current_directory();
		ft_update_or_add_var("PWD", new_path, shell);
		ft_free(new_path);
	}
}

static void	ft_handle_cd_to_dir(t_shell *shell, t_token *curr, char *curr_path)
{
	char	*path;
	char	*new_path;

	path = curr->next->value;
	if (chdir(path) == SUCCESS)
	{
		new_path = ft_get_current_directory();
		ft_update_or_add_var("PWD", new_path, shell);
		ft_update_or_add_var("OLDPWD", curr_path, shell);
		ft_free(new_path);
	}
	else
		ft_printf(2, "Path not found %s\n", path);
}
