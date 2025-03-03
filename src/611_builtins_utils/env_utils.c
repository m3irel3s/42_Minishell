/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/03 11:14:47 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_count_equals(char **n_env);

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
	env_cpy = ft_safe_calloc(sizeof(char *) * (i + 1));
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

void	ft_update_env(t_shell *shell)
{
	char	**n_env;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = ft_count_equals(shell->env_cpy);
	n_env = ft_safe_calloc(sizeof(char *) * (count + 1));
	while (shell->env_cpy[i])
	{
		if (ft_strchr(shell->env_cpy[i], '='))
			n_env[j++] = ft_safe_strdup(shell->env_cpy[i]);
		i++;
	}
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = n_env;
}

static int	ft_count_equals(char **n_env)
{
	int	count;

	count = 0;
	while (n_env[count])
	{
		if (ft_strchr(n_env[count], '='))
			count++;
		else
			count++;
	}
	return (count);
}
