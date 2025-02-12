/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:19 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 10:31:34 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_shell *shell)
{
	char	**env;
	int		i = 0;
	env = shell->dup_env;
	// while (env[i])
	// {
	// 	if (env[i] == NULL)
	// 		break ;
	// 	if ((ft_strncmp(env[i], "OLDPWD", 6) == SUCCESS) || ft_strncmp(env[i], "PWD", 3) == SUCCESS)
	// 		printf("%s\n", env[i]);
	// 	i++;
	// }
	while (env[i])
	{
		char *res = env[i];
		printf("%s\n", res);
		// free(res);
		i++;
	}
	return ;
}
