/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:01:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/11 13:48:47 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_path_errors(char *cmd)
{
	struct stat	path_stat;

	if (!ft_strchr(cmd, '/'))
	{
		ft_print_error_w_arg(ERR_CMD_NOT_FOUND, cmd, EXIT_CMD_NOT_FOUND);
		return ;
	}
	if (access(cmd, F_OK) == -1)
		ft_print_error_w_arg(ERR_NO_SUCH_FILE, cmd, EXIT_NO_SUCH_FILE);
	else if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		ft_print_error_w_arg(ERR_IS_A_DIRECTORY, cmd, EXIT_IS_A_DIRECTORY);
	else if (access(cmd, X_OK) == -1)
		ft_print_error_w_arg(ERR_PERM_DENIED, cmd, EXIT_PERM_DENIED);
}

void	ft_check_is_dir(t_shell *shell, char *path, char **arr)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_print_error_w_arg(ERR_IS_A_DIRECTORY, path, EXIT_IS_A_DIRECTORY);
		ft_cleanup_cmd_execution(path, arr);
		ft_cleanup(shell);
		if (shell->env_cpy)
			ft_free_arr(shell->env_cpy);
		exit(126);
	}
}
