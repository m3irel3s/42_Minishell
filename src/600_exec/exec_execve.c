/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 11:11:45 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_count_type_words(t_token *start_pos);

void	ft_execute_cmd(t_shell *shell, char *cmd)
{
	char	*path;
	char	**arr;
	pid_t	pid;

	arr = NULL;
	path = ft_get_path_to_execute(shell, cmd);
	arr = ft_create_arr_cmd(shell->tokens);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return ;
	}
	if (pid == 0)
	{
		if (execve(path, arr, shell->env_cpy) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

char	*ft_get_path_to_execute(t_shell *shell, char *cmd)
{
	char	*full_path;
	char	**arr;

	full_path = ft_get_var_value("PATH", shell->env_cpy);
	if (!full_path)
		return (NULL);
	arr = ft_split(full_path, ':');
	full_path = ft_add_cmd_to_path(arr, cmd);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*ft_add_cmd_to_path(char **arr, char *cmd)
{
	char	**cmd_arr;
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	cmd_arr = ft_split(cmd, ' ');
	while (arr[i])
	{
		arr[i] = ft_strjoin_gnl(arr[i], "/");
		full_path = ft_strjoin(arr[i], cmd_arr[0]);
		if (access(full_path, X_OK) == SUCCESS)
			return (ft_free_arr(arr), ft_free_arr(cmd_arr), full_path);
		ft_free(full_path);
		i++;
	}
	return (ft_free_arr(arr), ft_free_arr(cmd_arr), NULL);
}

char	**ft_create_arr_cmd(t_token *start_pos)
{
	t_token	*curr;
	char	**arr;
	int		i;

	i = 0;
	arr = NULL;
	curr = start_pos;
	i = ft_count_type_words(curr);
	arr = ft_safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	curr = start_pos;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == WORD)
			arr[i++] = ft_strdup_safe(curr->value);
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

