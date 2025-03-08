/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 22:46:37 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		ft_cleanup_cmd_execution(char *path, char **arr);
static t_status	ft_exec_child(t_shell *shell, char *path, char **arr);
static void		ft_handle_child_process(t_shell *shell, char *path, char **arr);

/**
 * @brief Executes a command in a child process.
 *
 * @details
 * This function takes a command as argument and executes it in a child process.
 * It first gets the path to the command and then creates an array of arguments
 * from the shell tokens. It then calls the ft_handle_child_process function to
 * fork and execute the command in a child process. Finally, it cleans up the
 * command execution.
 *
 * @param [in] shell The shell structure to execute the command in.
 * @param [in] cmd The command to execute.
 */
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

/**
 * @brief Handles the child process after forking to execute a command.
 *
 * Checks the return value of the fork call and handles the child process
 * execution accordingly. If the fork fails, it prints an error message,
 * cleans up the command execution resources and returns. If the fork is
 * successful, it executes the command in the child process if it's the
 * child process, or waits for the child process to finish and handles its
 * exit status if it's the parent process.
 *
 * @param shell The shell structure.
 * @param path The path to the command to execute.
 * @param arr The array of arguments to pass to the command.
 */
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
			g.g_exit_status = WEXITSTATUS(status);
	}
}

/**
 * @brief Frees the memory allocated for the command path and arguments.
 *
 * @details
 * This function takes a command path and an array of arguments and frees the
 * memory allocated for both. It is used to clean up after command execution.
 *
 * @param [in] path The path to the command to free.
 * @param [in] arr The array of arguments to free.
 */
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
		exit(g.g_exit_status);
	}
	return (SUCCESS);
}
