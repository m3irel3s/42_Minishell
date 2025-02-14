/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 16:24:06 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_duplicate_env(char **envp)
{
	char	**env_cpy;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env_cpy = NULL;
	while (envp[i])
		i++;
	env_cpy = ft_safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env_cpy[i] = ft_strdup_safe(envp[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	ft_get_env_size(t_shell *shell)
{
	int		i;
	char	**env;

	env = shell->env_cpy;
	i = 0;
	if (!env)
		return (-1);
	while (env[i])
		i++;
	return (i);
}

