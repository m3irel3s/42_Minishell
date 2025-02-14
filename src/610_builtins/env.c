/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:19 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 11:51:17 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_shell *shell)
{
	char	**env;
	char	*res;
	int		i;

	i = 0;
	env = shell->env_cpy;
	while (env[i])
	{
		res = env[i];
		printf("%s\n", res);
		i++;
	}
	return ;
}
