/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:40:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 15:30:15 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	ft_add_var_to_env(char *var, char *value, t_shell *shell)
{
	int		last_index;
	char	*new_entry;
	int		i;
	int		j;
	char	**env = shell->dup_env;

	last_index = ft_get_env_size(shell);
	new_entry = ft_safe_malloc(ft_get_str_length(var, value) + 2);
	i = 0;
	while(var[i])
	{
		new_entry[i] = var[i];
		i++;
	}
	new_entry[i++] = '=';
	j = 0;
	while(value[j])
		new_entry[i++] = value[j++];
	new_entry[i] = '\0';
	env[last_index] = new_entry;
}

int	ft_get_env_size(t_shell *shell)
{
	int		i;
	char	**env;

	env = shell->dup_env;
	i = 0;
	if (!env)
		return (-1);
	while (env[i])
		i++;
	return (i);
}

int	ft_get_str_length(char *str1, char *str2)
{
	return (ft_strlen(str1) + ft_strlen(str2));
}