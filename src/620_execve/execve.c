/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 14:57:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_cleanup_cmd_execution(char *path, char **arr);
static t_status	ft_exec_child(t_shell *shell, char *path, char **arr);
static void		ft_handle_child_process(t_shell *shell, char *path, char **arr);

void	ft_execute_cmd(t_shell *shell, char *cmd)
{
	char	*path;
	char	**arr;

	if (!cmd || !shell)
	{
		ft_print_error(ERR_INVALID_PARAMS);
		return ;
	}
	path = ft_get_path_to_execute(shell, cmd);
	if (!path)
	{
		ft_print_error_w_arg(ERR_CMD_NOT_FOUND, cmd, EXIT_CMD_NOT_FOUND);
		return ;
	}
	arr = ft_create_arr_cmd(shell->tokens);
	if (!arr)
	{
		ft_free(path);
		ft_print_error(ERR_MALLOC_FAIL);
		return ;
	}
	ft_handle_child_process(shell, path, arr);
	ft_cleanup_cmd_execution(path, arr);
}

static void	ft_handle_child_process(t_shell *shell, char *path, char **arr)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_print_error(ERR_FORK_FAIL);
		ft_cleanup_cmd_execution(path, arr);
		return ;
	}
	if (pid == 0)
		ft_exec_child(shell, path, arr);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

static void	ft_cleanup_cmd_execution(char *path, char **arr)
{
	ft_free(path);
	ft_free_arr(arr);
}

/**
 * @brief Executes a command in a child process.
 *
 * @details
 * This function forks a new process and executes the given command in it.
 * If the execve fails, it prints an error message, cleans up the command
 * execution, cleans up the shell, and exits with EXIT_FAILURE.
 *
 * @param [in] shell The shell structure to execute the command in.
 * @param [in] path The path to the command to execute.
 * @param [in] arr The array of arguments to pass to the command.
 *
 * @return The status of the command execution.
 */
static t_status	ft_exec_child(t_shell *shell, char *path, char **arr)
{
	if (execve(path, arr, shell->env_cpy) == -1)
	{
		ft_print_error_w_arg(ERR_CMD_NOT_FOUND, shell->tokens->val.value,
			EXIT_CMD_NOT_FOUND);
		ft_cleanup_cmd_execution(path, arr);
		ft_cleanup(shell);
		if (shell->env_cpy)
			ft_free_arr(shell->env_cpy);
		exit(g_exit_status);
	}
	return (SUCCESS);
}
