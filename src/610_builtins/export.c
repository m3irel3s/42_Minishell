/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/14 17:38:08 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_process_export_variable(t_shell *shell, char *arg);
static void	ft_append_to_var(t_shell *shell, char *var, char *new_value);
static int	ft_process_export_variable(t_shell *shell, char *arg);
static void	ft_handle_export_oper(t_shell *sh, char *arg, char *eq, char *plus);

/**
 * Processes the export command, either printing the list of exported variables
 * if no arguments are given, or adding/removing variables to/from the list of
 * exported variables according to the arguments.
 *
 * @param shell The minishell state.
 */
void	ft_export(t_shell *shell)
{
	t_token	*curr;

	g_exit_status = EXIT_SUCCESS;
	curr = shell->tokens;
	signal(SIGPIPE, SIG_IGN);
	if (!curr->next)
	{
		ft_print_export(shell);
		return ;
	}
	while (curr->next)
	{
		curr = curr->next;
		if (ft_process_export_variable(shell, curr->val.value) == EXIT_FAILURE)
			g_exit_status = EXIT_FAILURE;
	}
}

/**
 * Processes a single variable declaration for the export command.
 *
 * @param shell The minishell state.
 * @param arg The variable declaration string.
 *
 * @return EXIT_SUCCESS if the variable declaration is valid, EXIT_FAILURE
 * otherwise.
 *
 * @note This function does not handle the case of a variable declaration
 * without a value. In this case, the variable is simply added to the list of
 * exported variables with an empty value.
 *
 * @note This function does not handle the case of a variable declaration with
 * an invalid value. In this case, the variable is not added to the list of
 * exported variables.
 *
 * @note If the variable declaration is invalid, the function prints an error
 * message and returns EXIT_FAILURE.
 */
static int	ft_process_export_variable(t_shell *shell, char *arg)
{
	char	*eq_sign;
	char	*plus_sign;
	char	*var;

	eq_sign = ft_strchr(arg, '=');
	plus_sign = ft_strchr(arg, '+');
	if (ft_check_var_chars(arg) != SUCCESS)
	{
		return (ft_print_error_w_arg(\
		ERR_EXPORT_INVALID_IDENTIFIER, arg, EXIT_FAILURE), EXIT_FAILURE);
	}
	ft_handle_export_oper(shell, arg, eq_sign, plus_sign);
	var = ft_get_var_name(arg);
	if (!var)
		return (EXIT_FAILURE);
	return (ft_free(var), EXIT_SUCCESS);
}

/**
 * Handles the export command operator (+/=) for a single variable declaration.
 *
 * @param sh The minishell state.
 * @param arg The variable declaration string.
 * @param eq The position of the '=' character in the string.
 * @param plus The position of the '+' character in the string.
 *
 * @note This function handles three cases:
 *  - If the '+' character is present and is followed by the '=' character,
 *    the variable is appended to the list of exported variables with the
 *    value that follows the '=' character.
 *  - If only the '=' character is present, the variable is added to the list
 *    of exported variables with the value that follows the '=' character.
 *  - If neither the '+' nor the '=' characters are present, and the variable
 *    is not already in the list of exported variables, the variable is added
 *    to the list with an empty value.
 *
 * @note This function frees the variable name string after use.
 */
static void	ft_handle_export_oper(t_shell *sh, char *arg, char *eq, char *plus)
{
	char	*var;
	char	*value;

	var = NULL;
	if (plus && eq && plus + 1 == eq)
	{
		var = ft_substr(arg, 0, plus - arg);
		value = eq + 1;
		ft_append_to_var(sh, var, value);
	}
	else if (eq)
	{
		var = ft_substr(arg, 0, eq - arg);
		value = eq + 1;
		ft_update_or_add_var(var, value, sh, 0);
	}
	else if (ft_get_var_index(arg, sh->env_cpy) == -1)
	{
		var = ft_safe_strdup(arg);
		value = "";
		ft_update_or_add_var(var, value, sh, -1);
	}
	ft_free(var);
}

/**
 * @brief Adds a new variable to the shell's environment.
 *
 * This function creates a new environment array that includes the
 * specified variable and its value. If the environment allocation
 * fails, the function returns without making any changes. The new
 * variable is appended to the end of the current environment array.
 *
 * @param shell The shell structure containing the environment.
 * @param var The name of the variable to be added.
 * @param value The value of the variable to be added.
 * @param sign Determines how the value is constructed when updating a variable.
 */
void	ft_add_var_to_env(t_shell *shell, char *var, char *value, int sign)
{
	char	**new_env;
	int		new_size;
	int		i;

	i = 0;
	new_size = ft_get_env_size(shell) + 1;
	new_env = ft_safe_calloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return ;
	while (shell->env_cpy[i])
	{
		new_env[i] = ft_safe_strdup(shell->env_cpy[i]);
		if (!new_env[i])
		{
			ft_free_arr(new_env);
			return ;
		}
		i++;
	}
	new_env[i] = ft_update_var(var, value, sign);
	new_env[i + 1] = NULL;
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = new_env;
}

/**
 * @brief Appends a new value to an existing environment variable.
 *
 * This function locates the specified variable in the shell's environment.
 * If the variable exists, it appends the new value to the existing value
 * and updates the variable. If the variable does not exist, it adds a new
 * variable with the given value. The function ensures memory is managed
 * properly, freeing any old values as necessary.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param var The name of the variable to be updated.
 * @param new_value The value to append to the existing variable.
 */
static void	ft_append_to_var(t_shell *shell, char *var, char *new_value)
{
	char	*full_value;
	char	*old_value;
	char	*new_var;
	int		var_index;

	var_index = ft_get_var_index(var, shell->env_cpy);
	if (var_index == -1)
	{
		ft_update_or_add_var(var, new_value, shell, 0);
		return ;
	}
	old_value = ft_get_var_value(var, shell->env_cpy);
	full_value = ft_safe_strjoin(old_value, new_value, 0);
	new_var = ft_update_var(var, full_value, 0);
	ft_free(shell->env_cpy[var_index]);
	shell->env_cpy[var_index] = new_var;
	ft_free(full_value);
}
