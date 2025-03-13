/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:35:08 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/13 10:34:45 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Creates a new string by updating the value of an environment variable.
 *
 * Updates the value of an environment variable by appending the new value
 * to the variable name with '=' in between. If the sign is -1, the value will
 * not be appended.
 *
 * @param var The name of the environment variable.
 * @param value The new value for the environment variable.
 * @param sign If sign is -1, the value will not be appended.
 * @return The new string with the updated value.
 */
char	*ft_update_var(char *var, char *value, int sign)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (sign == -1)
		res = ft_safe_calloc(ft_get_str_length(var, value) + 1);
	else
		res = ft_safe_calloc(ft_get_str_length(var, value) + 2);
	while (var[i])
	{
		res[i] = var[i];
		i++;
	}
	if (sign == -1)
		res[i] = '\0';
	else
	{
		res[i++] = '=';
		j = 0;
		while (value[j])
			res[i++] = value[j++];
		res[i] = '\0';
	}
	return (res);
}

/**
 * @brief Updates or adds an environment variable to the shell's environment.
 *
 * Checks if the variable exists in the shell's environment. If it does, it
 * updates the value of the variable using ft_update_var. If it does not, it
 * adds the variable to the shell's environment using ft_add_var_to_env.
 *
 * @param var The name of the environment variable.
 * @param value The new value for the environment variable.
 * @param shell A pointer to the shell structure.
 * @param sign If sign is -1, the value will not be appended when updating the
 * variable.
 */
void	ft_update_or_add_var(char *var, char *value, t_shell *shell, int sign)
{
	int		var_index;
	char	*new_var;

	new_var = NULL;
	var_index = ft_get_var_index(var, shell->env_cpy);
	if (var_index == -1)
	{
		ft_add_var_to_env(shell, var, value, sign);
		return ;
	}
	new_var = ft_update_var(var, value, sign);
	ft_free(shell->env_cpy[var_index]);
	shell->env_cpy[var_index] = new_var;
	return ;
}
