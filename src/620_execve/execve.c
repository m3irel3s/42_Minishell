/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		ft_count_type_words(t_token *start_pos);
static void		ft_cleanup_cmd_execution(char *path, char **arr);
static t_status	ft_exec_child(t_shell *shell, char *path, char **arr);

void	ft_execute_cmd(t_shell *shell, char *cmd)
{
	char	*path;
	char	**arr;
	pid_t	pid;
	int		status;

	if (!cmd || !shell)
	{
		ft_print_error(ERR_INVALID_PARAMS);
		return ;
	}
	path = ft_get_path_to_execute(shell, cmd);
	if (!path)
	{
		ft_print_command_not_found_error(cmd);
		return ;
	}
	arr = ft_create_arr_cmd(shell->tokens);
	if (!arr)
	{
		ft_free(path);
		ft_print_error(ERR_MALLOC_FAIL);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (ft_print_error(ERR_FORK_FAIL), ft_cleanup_cmd_execution(path, arr));
	if (pid == 0)
		ft_exec_child(shell, path, arr);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
	ft_cleanup_cmd_execution(path, arr);
}

char	*ft_get_path_to_execute(t_shell *shell, char *cmd)
{
	char	*full_path;
	char	**arr;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_safe_strdup(cmd));
	full_path = ft_get_var_value("PATH", shell->env_cpy);
	if (!full_path)
		return (NULL);
	arr = ft_split(full_path, ':');
	if (!arr)
		return (NULL);
	full_path = ft_add_cmd_to_path(arr, cmd);
	return (full_path);
}

char	*ft_add_cmd_to_path(char **arr, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (arr[i])
	{
		arr[i] = ft_safe_strjoin(arr[i], "/", 1);
		full_path = ft_safe_strjoin(arr[i], cmd, 0);
		if (access(full_path, X_OK) == SUCCESS)
		{
			ft_free_arr(arr);
			return (full_path);
		}
		ft_free(full_path);
		i++;
	}
	ft_free_arr(arr);
	return (NULL);
}

char	**ft_create_arr_cmd(t_token *start_pos)
{
	t_token	*curr;
	char	**arr;
	int		i;

	if (!start_pos)
		return (NULL);
	i = ft_count_type_words(start_pos);
	arr = ft_safe_malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	curr = start_pos;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == WORD)
			arr[i++] = ft_safe_strdup(curr->val.value);
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}

static int	ft_count_type_words(t_token *start_pos)
{
	int	counter;

	counter = 0;
	while (start_pos && start_pos->type != PIPE)
	{
		if (start_pos->type == WORD)
			counter++;
		start_pos = start_pos->next;
	}
	return (counter);
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
		ft_print_command_not_found_error(shell->tokens->val.value);
		ft_cleanup_cmd_execution(path, arr);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}
