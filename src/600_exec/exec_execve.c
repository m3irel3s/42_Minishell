/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:25 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 15:56:44 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute_cmd(t_shell *shell, char *cmd)
{
	char	*path;
	char	**arr;
	arr = NULL;
	path = ft_get_path_to_execute(shell, cmd);
	arr = ft_create_arr_cmd(shell->tokens);
	execve(path, arr, shell->env_cpy);
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
	{
		ft_printf(2, "Command not found %s\n", cmd);
		return (NULL);
	}
	printf("%s\n", full_path);
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
	while (curr && curr->type != PIPE)
	{
		if(curr->type == WORD)
			i++;
		curr = curr->next;
	}
	curr = start_pos;
	arr = ft_safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == WORD)
			arr[i++] = ft_strdup_safe(curr->value);
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}
