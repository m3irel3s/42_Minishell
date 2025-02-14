/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:35:08 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 12:19:40 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_update_var(char *var, char *value)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	res = ft_safe_malloc(ft_get_str_length(var, value) + 2);
	while (var[i])
	{
		res[i] = var[i];
		i++;
	}
	res[i++] = '=';
	j = 0;
	while (value[j])
		res[i++] = value[j++];
	res[i] = '\0';
	return res;
}

void	ft_update_or_add_var(char *var, char *value, t_shell *shell)
{
	int		var_index;
	char	*new_var;

	new_var = NULL;
	var_index = ft_get_var_index(var, shell->env_cpy);
	if (var_index == -1)
	{
		ft_add_var_to_env(shell, var, value);
		return ;
	}
	new_var = ft_update_var(var, value);
	free(shell->env_cpy[var_index]);
	shell->env_cpy[var_index] = new_var;
	return ;
}
