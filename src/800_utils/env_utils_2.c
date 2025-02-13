/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:40:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 15:02:36 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_var_to_env(char *var, char *value, t_shell *shell)
{
	(void)var;
	(void)value;
	(void)shell;
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





