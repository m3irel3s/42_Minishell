/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:19 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/24 10:19:09 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	ft_env(t_shell *shell)
{
	char	**env;
	int		i;

	i = 0;
	env = shell->env_cpy;
	res = NULL;
	while (env[i])
	{
		res = ft_get_var_value(ft_get_var_name(env[i]), env);
		if (res != NULL)
			ft_printf(STDOUT_FILENO, "%s\n", env[i]);
		i++;
	}
	g_exit_status = EXIT_SUCCESS;
}
