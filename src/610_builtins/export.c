/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/24 09:35:33 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_process_export_variable(t_shell *shell, char *arg);
	// valid names - Must start with a letter or '_', and contain only letters or numbers ######
	// print export ####
	// add new variable
	// if it exists, overwrite, if it is "+=" append
	// if doenst exist, give empty value if nothing has been assigned

	// 0 no quote
	// 1 single quote
	// 2 double quote

// static void	ft_append_to_var(t_shell *shell, char *var, char *new_value);

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
	char	*var;
	char	*value;
	char	*eq_sign;
	char	*error_msg;

	if (ft_check_var_chars(arg) != SUCCESS)
	{
		error_msg = ft_format_error(ERR_EXPORT_INVALID_IDENTIFIER, arg);
		ft_print_error(error_msg);
		ft_free(error_msg);
		return (EXIT_FAILURE);
	}
	var = ft_get_var_name(arg);
	if (!var)
		return (EXIT_FAILURE);
	eq_sign = ft_strchr(arg, '=');
	if (eq_sign)
		value = eq_sign + 1;
	else
		value = NULL;
	ft_update_or_add_var(var, value, shell);
	ft_free(var);
	return (EXIT_SUCCESS);
}

void	ft_add_var_to_env(t_shell *shell, char *var, char *value)
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
	new_env[i] = ft_update_var(var, value);
	new_env[i + 1] = NULL;
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = new_env;
}

// ### Function to handle the append +=
// ### ex: a=ola a+=ola res: a=olaola
// ### Still an error variable needs to be received without the + , ft_substr might help

/* static void	ft_append_to_var(t_shell *shell, char *var, char *new_value)
{
	char	*full_value;
	char	*old_value;
	char	*new_var;
	int		var_index;

	var_index = ft_get_var_index(var, shell->env_cpy);
	old_value = ft_get_var_value(var, shell->env_cpy);
	full_value = ft_safe_strjoin(old_value, new_value,);
	new_var = ft_update_var(var, full_value);
	ft_free(shell->env_cpy[var_index]);
	shell->env_cpy[var_index] = new_var;
} */


