/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/17 10:48:17 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_exec_child(t_shell *shell, char *path, char **arr);
static void	ft_exec_parent(t_shell *shell, pid_t pid, int status,
				struct sigaction old_sa);
static void	ft_handle_child_process(t_shell *shell, char *path, char **arr);

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
		ft_print_path_errors(cmd);
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
 * @brief Forks a new process and executes a command in it.
 *
 * @details
 * This function takes a command path and an array of arguments and forks a new
 * process to execute the command. It sets up the SIGINT signal handler so that
 * any SIGINT signals are ignored while the child is executing. It executes the
 * command in the child process and waits for it to finish in the parent
 * process. It then cleans up the child process and resets the SIGINT signal
 * handler.
 *
 * @param [in] shell The shell structure to execute the command in.
 * @param [in] path The path to the command to execute.
 * @param [in] arr The array of arguments to pass to the command.
 */
static void	ft_handle_child_process(t_shell *shell, char *path, char **arr)
{
	pid_t				pid;
	int					status;
	struct sigaction	old_sa;
	struct sigaction	ignore_sa;

	status = 0;
	if (ft_setup_sigint_ignore(&ignore_sa, &old_sa) == ERROR)
		return ;
	pid = fork();
	if (pid == -1)
	{
		ft_print_error(ERR_FORK_FAIL);
		ft_cleanup_cmd_execution(path, arr);
		sigaction(SIGINT, &old_sa, NULL);
		return ;
	}
	if (pid == 0)
		ft_exec_child(shell, path, arr);
	else
		ft_exec_parent(shell, pid, status, old_sa);
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
void	ft_cleanup_cmd_execution(char *path, char **arr)
{
	ft_free(path);
	ft_free_arr(arr);
}

/**
 * @brief Executes a command in a child process.
 *
 * @details
 * This function is called after a fork and executes the given command in the
 * child process. If the execve call fails, it prints an error message and
 * exits with the exit status set to EXIT_CMD_NOT_FOUND.
 *
 * @param [in] shell The shell structure to execute the command in.
 * @param [in] path The path to the command to execute.
 * @param [in] arr The array of arguments to the command.
 */

static void	ft_exec_child(t_shell *shell, char *path, char **arr)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	ft_check_is_dir(shell, path, arr);
	if (execve(path, arr, shell->env_cpy) == -1)
	{
		if (errno == EACCES)
		{
			ft_free(shell->last_cwd);
			ft_print_error_w_arg(ERR_PERM_DENIED, path, EXIT_PERM_DENIED);
		}
		else
		{
			ft_free(shell->last_cwd);
			ft_print_error_w_arg(ERR_CMD_NOT_FOUND, path, EXIT_CMD_NOT_FOUND);
		}
		ft_cleanup_cmd_execution(path, arr);
		ft_cleanup_w_env(shell);
		exit(g_exit_status);
	}
}

/**
 * @brief Handles the parent process after forking for command execution.
 *
 * This function waits for the child process to finish and handles its
 * exit status and signals. If the child process was interrupted by a
 * signal, it prints a new line and sets the shell's exit status to
 * EXIT_FAILURE. Otherwise, it sets the shell's exit status to the
 * child process's exit status.
 *
 * @param pid The process ID of the forked child process.
 * @param status The exit status of the child process.
 * @param old_sa The original SIGINT handler to restore.
 */
static void	ft_exec_parent(t_shell *shell, pid_t pid, int status,
						struct sigaction old_sa)
{
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &old_sa, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		if (dup2(shell->og_stdout, STDOUT_FILENO) == -1)
			ft_print_error(ERR_DUP2_FAIL);
		write(STDOUT_FILENO, "\n", 1);
		ft_cleanup(shell);
		g_exit_status = EXIT_SIGINT;
	}
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
