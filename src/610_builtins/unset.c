/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:01 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/14 17:41:15 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status	ft_remove_var(t_shell *shell, char **new_env, int var_index);
static t_status	ft_remove_var_update_env(t_shell *shell, char *var);
static t_status	ft_is_valid_var_name(char *var);

/**
 * @brief Unsets environment variables specified by the tokens in the shell
 * structure.
 *
 * Iterates over tokens linked list in the shell structure, starting from the
 * second token. For each token, it checks if the token's value is a valid
 * variable name. If valid and the variable exists in the environment, removes
 * it by updating the environment. Sets the global exit status to success after
 * processing all tokens.
 *
 * @param shell A pointer to the shell structure containing tokens and
 * environment.
 */
void	ft_unset(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	if (!curr->next)
		return ;
	while (curr->next)
	{
		curr = curr->next;
		if (ft_is_valid_var_name(curr->val.value) == ERROR)
			g_exit_status = EXIT_SUCCESS;
		else if (ft_get_var_index(curr->val.value, shell->env_cpy) != -1)
			if (ft_remove_var_update_env(shell, curr->val.value) == ERROR)
				g_exit_status = EXIT_SUCCESS;
	}
	g_exit_status = EXIT_SUCCESS;
}

/**
 * @brief Updates the shell's environment by removing the specified variable.
 *
 * If the variable exists in the environment, allocates a new array of strings
 * without the specified variable and updates the shell's environment. Frees the
 * old environment array.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param var The name of the variable to be removed.
 * @return The status of the operation (ERROR or SUCCESS).
 */
static t_status	ft_remove_var_update_env(t_shell *shell, char *var)
{
	char	**new_env;
	int		var_index;

	var_index = ft_get_var_index(var, shell->env_cpy);
	new_env = ft_safe_calloc(sizeof(char *) * (ft_get_env_size(shell)));
	if (!new_env)
		return (ERROR);
	ft_remove_var(shell, new_env, var_index);
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = ft_duplicate_env(new_env);
	ft_free_arr(new_env);
	return (SUCCESS);
}

/**
 * @brief Creates a new array of strings without the specified variable.
 *
 * Iterates over the shell's environment array, and for each variable, it checks
 * if the index is not equal to the specified index. If the index is not equal,
 * it allocates memory for a new string and copies the old string to the new
 * string. It then increments the index in the new array. At the end, it sets the
 * last element of the new array to NULL and returns SUCCESS. If memory
 * allocation fails, it frees the new array and returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param new_env The new array of strings to be filled.
 * @param var_index The index of the variable to be removed.
 * @return The status of the operation (ERROR or SUCCESS).
 */
static t_status	ft_remove_var(t_shell *shell, char **new_env, int var_index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env_cpy[i])
	{
		if (i != var_index)
		{
			new_env[j] = ft_safe_strdup(shell->env_cpy[i]);
			if (!new_env[j++])
			{
				ft_free_arr(new_env);
				return (ERROR);
			}
		}
		i++;
	}
	new_env[j] = NULL;
	return (SUCCESS);
}

/**
 * @brief Checks if the given string is a valid variable name.
 *
 * This function verifies whether a string can be considered a valid
 * environment variable name. A valid variable name must start with a
 * non-digit character and may only contain alphanumeric characters or
 * underscores ('_'). If the name is valid, the function returns SUCCESS;
 * otherwise, it returns ERROR.
 *
 * @param var The string to be checked as a potential variable name.
 * @return The status of the validation (ERROR or SUCCESS).
 */
static t_status	ft_is_valid_var_name(char *var)
{
	int	i;

	if (!var || !*var || ft_isdigit(*var))
		return (ERROR);
	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
