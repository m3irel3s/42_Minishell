/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/24 14:53:20 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_process_export_variable(t_shell *shell, char *arg);
	// valid names - Must start with a letter or '_', and contain only letters or numbers ######
	// print export ####
	// add new variable
	// if it exists, overwrite, if it is "+=" append
	// if doenst exist, give empty value if nothing has been assigned
	//when just doing export var, if var exists doesnt change its value to empty

	// 0 no quote
	// 1 single quote
	// 2 double quote

static void	ft_append_to_var(t_shell *shell, char *var, char *new_value);
static int	ft_process_export_variable(t_shell *shell, char *arg);
static void		ft_handle_export_oper(t_shell *shell, char *arg, char *eq_sign, char *plus_sign);


void	ft_export(t_shell *shell)
{
	t_token *curr;

	g_exit_status = EXIT_SUCCESS;
	curr = shell->tokens;
	if (!curr->next)
	{
		ft_print_export(shell);
		return ;
	}
	while (curr->next)
	{
		curr = curr->next;
		if (ft_process_export_variable(shell, curr->value) == EXIT_FAILURE)
			g_exit_status = EXIT_FAILURE;
	}
}

static int	ft_process_export_variable(t_shell *shell, char *arg)
{
	char	*error_msg;
	char	*eq_sign;
	char	*plus_sign;
	char	*var;

	eq_sign = ft_strchr(arg, '=');
	plus_sign = ft_strchr(arg, '+');
	if (ft_check_var_chars(arg) != SUCCESS)
	{
		error_msg = ft_format_error(ERR_EXPORT_INVALID_IDENTIFIER, arg);
		return (ft_print_error(error_msg), ft_free(error_msg), EXIT_FAILURE);
	}
	ft_handle_export_oper(shell, arg, eq_sign, plus_sign);
	var = ft_get_var_name(arg);
	if (!var)
		return (EXIT_FAILURE);
	return (ft_free(var), EXIT_SUCCESS);
}

static void	ft_handle_export_oper(t_shell *shell, char *arg, char *eq_sign, char *plus_sign)
{
	char	*var;
	char	*value;

	var = NULL;
	if (plus_sign && eq_sign && plus_sign + 1 == eq_sign)
	{
		var = ft_substr(arg, 0, plus_sign - arg);
		value = eq_sign + 1;
		ft_append_to_var(shell, var, value);
	}
	else if (eq_sign)
	{
		var = ft_substr(arg, 0, eq_sign - arg);
		value = eq_sign + 1;
		ft_update_or_add_var(var, value, shell, 0);
	}
	else if (ft_get_var_index(arg, shell->env_cpy) == -1)
	{
		var = ft_safe_strdup(arg);
		value = "";
		ft_update_or_add_var(var, value, shell, -1);
	}
	ft_free(var);
}

void	ft_add_var_to_env(t_shell *shell, char *var, char *value, int sign)
{
	char	**new_env;
	int		new_size;
	int		i;

	i = 0;
	new_size = ft_get_env_size(shell) + 1;
	new_env = ft_safe_malloc(sizeof(char *) * (new_size + 1));
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


