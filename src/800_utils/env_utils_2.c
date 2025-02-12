/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:40:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 15:02:53 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	ft_add_var_to_env(char *var_name, char *var_value, t_shell *shell)
{
	(void)var_name;
	(void)shell;
	(void)var_value;
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