/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 17:50:08 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

	// valid names - Must start with a letter or '_', and contain only letters or numbers ######
	// print export ####
	// add new variable
	// if it exists, overwrite, if it is "+=" append
	// if doenst exist, give empty value if nothing has been assigned

	// 0 no quote
	// 1 single quote
	// 2 double quote

static void	ft_append_to_var(t_shell *shell, char *var, char *new_value);
static void	ft_handle_export_args(t_shell *shell, char *agr);

void	ft_export(t_shell *shell)
{
	t_token *curr;

	curr = shell->tokens->next;
	if (!curr)
	{
		ft_print_export(shell);
		return ;
	}
	while (curr)
	{
		if (ft_check_var_chars(curr->value) != SUCCESS)
		{
			curr = curr->next;
			continue;
		}
		ft_handle_export_args(shell, curr->value);
		curr = curr->next;
	}
}

static void	ft_handle_export_args(t_shell *shell, char *arg)
{
	char	*eq_sign;
	char	*plus_sign;
	char	*var;
	char	*value;

	eq_sign = ft_strchr(arg, '=');
	plus_sign = ft_strchr(arg, '+');
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
		ft_update_or_add_var(var, value, shell);
	}
	else
	{
		var = ft_safe_strdup(arg);
		value = "";
		ft_update_or_add_var(var, value, shell);
	}
	ft_free(var);
}

void	ft_add_var_to_env(t_shell *shell, char *var, char *value)
{
	char	**new_env;
	int		new_size;
	int		i;

	i = 0;
	new_size = ft_get_env_size(shell) + 1;
	new_env = ft_safe_malloc(sizeof(char *) * (new_size + 1));
	while (shell->env_cpy[i])
	{
		new_env[i] = ft_safe_strdup(shell->env_cpy[i]);
		i++;
	}
	new_env[i++] = ft_update_var(var, value);
	new_env[i] = NULL;
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = ft_duplicate_env(new_env);
	ft_free_arr(new_env);
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
		ft_update_or_add_var(var, new_value, shell);
		return ;
	}
	old_value = ft_get_var_value(var, shell->env_cpy);
	full_value = ft_safe_strjoin(shell, old_value, new_value, 0);
	new_var = ft_update_var(var, full_value);
	ft_free(shell->env_cpy[var_index]);
	shell->env_cpy[var_index] = new_var;
}


