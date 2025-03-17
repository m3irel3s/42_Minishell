/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:01:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/17 10:34:00 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Prints an error message when a command cannot be executed.
 *
 * @details This function is used to print an error message when a command cannot
 * be executed. It checks if the command has a path, if the file exists, if the
 * file is a directory, and if the file has execute permissions. Depending on the
 * error, it prints the appropriate error message.
 *
 * @param cmd The command to be executed.
 */
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

/**
 * @brief Checks if a given path is a directory and prints an error message if
 * so.
 *
 * @details This function takes a path and an array of arguments, and checks
 * if the path is a directory. If it is, it prints an error message and exits
 * with a status of 126.
 *
 * @param shell A pointer to the shell structure.
 * @param path The path to check.
 * @param arr The array of arguments.
 */
void	ft_check_is_dir(t_shell *shell, char *path, char **arr)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_print_error_w_arg(ERR_IS_A_DIRECTORY, path, EXIT_IS_A_DIRECTORY);
		ft_cleanup_cmd_execution(path, arr);
		ft_cleanup_w_env(shell);
		exit(EXIT_IS_A_DIRECTORY);
	}
}
