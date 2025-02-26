/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:19 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 17:27:42 by meferraz         ###   ########.fr       */
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
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_printf(STDOUT_FILENO, "%s\n", env[i]);
		i++;
	}
	g_exit_status = EXIT_SUCCESS;
}
