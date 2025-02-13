/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:59 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:42 by jmeirele         ###   ########.fr       */
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
		ft_set_var_value("OLDPWD", ft_get_current_directory(), shell);
		chdir(ft_get_var_value("HOME", shell->dup_env));
		ft_set_var_value("PWD", ft_get_current_directory(), shell);
	}
	else if (ft_strncmp(current->next->value, "-", 2) == SUCCESS)
	{
		chdir(ft_get_var_value("OLDPWD", shell->dup_env));
		printf("%s\n", ft_get_var_value("OLDPWD", shell->dup_env));
		ft_set_var_value("OLDPWD", curr_path, shell);
		ft_set_var_value("PWD", ft_get_current_directory(), shell);
	}
	else
	{
		char *path;
		path = current->next->value;
		if (chdir(path) == SUCCESS)
		{
			ft_set_var_value("PWD", ft_get_current_directory(), shell);
			ft_set_var_value("OLDPWD", curr_path, shell);
		}
		else
			ft_printf(2, "Path not found %s\n", path);
	}
}
