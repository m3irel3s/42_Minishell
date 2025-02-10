/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/10 16:14:58 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_duplicate_env(char **envp)
{
	char **dup_env;
	int i;

	i = 0;
	dup_env = NULL;
	if (!envp[i] || !envp)
		return (NULL);
	while (envp[i])
		i++;
	dup_env = ft_safe_malloc(sizeof(char *) * i + 1);
	i = 0;
	while (envp[i])
	{
		dup_env[i] = ft_safe_malloc(ft_strlen(envp[i]) + 1);
		dup_env[i] = envp[i];
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

char	*ft_get_env_value(char *var, char **env)
{
	int i = 0;

	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == SUCCESS)
			return env[i] + ft_strlen(var) + 1;
		i++;
	}
	return (NULL);
}


