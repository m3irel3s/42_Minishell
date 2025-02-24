/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/24 09:50:17 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Duplicates the environment array.
 *
 * @param envp The original environment array to duplicate.
 * @return A newly allocated copy of the environment array, or NULL on failure.
 */
char	**ft_duplicate_env(char **envp)
{
	char	**env_cpy;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	env_cpy = ft_safe_malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_cpy[i] = ft_safe_strdup(envp[i]);
		if (!env_cpy[i])
		{
			ft_free_arr(env_cpy);
			return (NULL);
		}
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

/**
 * @brief Gets the size of the environment array.
 *
 * @param shell The shell structure containing the environment.
 * @return The number of environment variables, or -1 if the environment is NULL.
 */
int	ft_get_env_size(t_shell *shell)
{
	int		i;
	char	**env;

	env = shell->env_cpy;
	if (!env)
		return (-1);
	i = 0;
	while (env[i])
		i++;
	return (i);
}
