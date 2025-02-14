/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:59 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 12:19:10 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(t_shell *shell)
{
	t_token	*current;
	
	current = shell->tokens;
	char *curr_path = ft_get_current_directory();
	if (!current->next || ft_strncmp(current->next->value, "~", 2) == SUCCESS)
	{
		ft_update_or_add_var("OLDPWD", ft_get_current_directory(), shell);
		chdir(ft_get_var_value("HOME", shell->env_cpy));
		ft_update_or_add_var("PWD", ft_get_current_directory(), shell);
	}
	else if (ft_strncmp(current->next->value, "-", 2) == SUCCESS)
	{
		chdir(ft_get_var_value("OLDPWD", shell->env_cpy));
		printf("%s\n", ft_get_var_value("OLDPWD", shell->env_cpy));
		ft_update_or_add_var("OLDPWD", curr_path, shell);
		ft_update_or_add_var("PWD", ft_get_current_directory(), shell);
	}
	else
	{
		char *path;
		path = current->next->value;
		if (chdir(path) == SUCCESS)
		{
			ft_update_or_add_var("PWD", ft_get_current_directory(), shell);
			ft_update_or_add_var("OLDPWD", curr_path, shell);
		}
		else
			ft_printf(2, "Path not found %s\n", path);
	}
}
