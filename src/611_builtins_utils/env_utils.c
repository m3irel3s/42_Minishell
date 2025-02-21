/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 11:06:07 by meferraz         ###   ########.fr       */
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
		env_cpy[i] = ft_safe_strdup(envp[i]);
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
