/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:19 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/24 15:17:05 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	ft_env(t_shell *shell)
{
	char	**env;
	char	*eq_sign;
	int		i;

	i = 0;
	env = shell->env_cpy;
	eq_sign = NULL;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_printf(STDOUT_FILENO, "%s\n", env[i]);
		i++;
	}
	g_exit_status = EXIT_SUCCESS;
}
