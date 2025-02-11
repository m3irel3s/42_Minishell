/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:59 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 13:21:49 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(t_shell *shell)
{
	t_token	*current;
	
	current = shell->tokens;
	char *curr_path = getcwd(NULL, 0);
	if (!current->next || ft_strncmp(current->next->value, "~", 2) == SUCCESS)
	{
		ft_set_env_value("OLDPWD", getcwd(NULL, 0), shell->dup_env);
		chdir(ft_get_env_value("HOME", shell->dup_env));
		ft_set_env_value("PWD", getcwd(NULL, 0), shell->dup_env);
	}
	else if (ft_strncmp(current->next->value, "-", 2) == SUCCESS)
	{
		chdir(ft_get_env_value("OLDPWD", shell->dup_env));
		printf("%s\n", ft_get_env_value("OLDPWD", shell->dup_env));
		ft_set_env_value("OLDPWD", curr_path, shell->dup_env);
		ft_set_env_value("PWD", getcwd(NULL, 0), shell->dup_env);
	}
	else
	{
		char *path;
		path = current->next->value;
		if (chdir(path) == SUCCESS)
		{
			ft_set_env_value("PWD", getcwd(NULL, 0), shell->dup_env);
			ft_set_env_value("OLDPWD", curr_path, shell->dup_env);
		}
		else
			ft_printf(2, "Path not found %s", path);
	}
	return ;
}