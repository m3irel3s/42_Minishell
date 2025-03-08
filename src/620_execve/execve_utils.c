/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:54:34 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 15:04:38 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_count_type_words(t_token *start_pos);

/**
 * Retrieves the full path to the executable for a given command.
 *
 * @param shell A pointer to the shell structure containing environment
 * variables.
 * @param cmd The command for which to find the executable path.
 * @return A dynamically allocated string containing the full path to the
 * executable
 *         if found, or NULL if an error occurs or the command is not found.
 *         The caller is responsible for freeing the returned path.
 */

char	*ft_get_path_to_execute(t_shell *shell, char *cmd)
{
	char	*full_path;
	char	**arr;

	if (!cmd || cmd[0] == '\0')
	{
		ft_print_error(ERR_INVALID_PARAMS);
		return (NULL);
	}
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_safe_strdup(cmd));
	full_path = ft_get_var_value("PATH", shell->env_cpy);
	if (!full_path)
		return (NULL);
	arr = ft_split(full_path, ':');
	if (!arr)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		return (NULL);
	}
	full_path = ft_add_cmd_to_path(arr, cmd);
	return (full_path);
}

/**
 * Appends a command to all paths in an array and returns the first path to which
 * the command is executable.
 *
 * @param arr An array of paths. The array is modified to append a '/' character
 *            to each path.
 * @param cmd The command to append to each path.
 * @return The first full path to which the command is executable, or NULL if no
 *         such path exists. The caller is responsible for freeing the returned
 *         path.
 */
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

/**
 * Creates an array of command arguments from a token list.
 *
 * @param start_pos The start position of the token list
 * @return A dynamically allocated array of command arguments, or NULL if an
 *         error occurs.
 */
char	**ft_create_arr_cmd(t_token *start_pos)
{
	t_token	*curr;
	char	**arr;
	int		i;

	if (!start_pos)
		return (NULL);
	i = ft_count_type_words(start_pos);
	arr = ft_safe_calloc(sizeof(char *) * (i + 1));
	if (!arr)
	{
		ft_print_error(ERR_MALLOC_FAIL);
		return (NULL);
	}
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

/**
 * @brief Counts the number of words in a token list from the start position to
 * the first PIPE token.
 *
 * @param start_pos The start position of the token list
 * @return The number of words in the list
 */
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
