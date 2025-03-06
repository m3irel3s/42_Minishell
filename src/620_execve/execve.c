/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/06 11:12:49 by jmeirele         ###   ########.fr       */
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
		ft_print_error_w_arg(ERR_CMD_NOT_FOUND, cmd);
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

static t_status	ft_exec_child(t_shell *shell, char *path, char **arr)
{
	if (execve(path, arr, shell->env_cpy) == -1)
	{
		ft_print_error_w_arg(ERR_CMD_NOT_FOUND, shell->tokens->val.value);
		ft_cleanup_cmd_execution(path, arr);
		ft_cleanup(shell);
		if (shell->env_cpy)
			ft_free_arr(shell->env_cpy);
		exit(EXIT_FAILURE);
	}
	else
		return (SUCCESS);
}
