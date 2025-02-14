/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:07 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 15:44:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_duplicate_env(char **envp)
{
	char	**dup_env;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	dup_env = NULL;
	while (envp[i])
		i++;
	dup_env = ft_safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		dup_env[i] = ft_strdup_safe(envp[i]);
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

char	*ft_get_var_value(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == SUCCESS)
			return (env[i] + ft_strlen(var) + 1);
		i++;
	}
	return (NULL);
}

int	ft_get_var_index(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == SUCCESS)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_set_var_value(char *var, char *value, t_shell *shell)
{
	int		index;
	int		i;
	int		j;
	char	*res = NULL;
	char	**env = shell->dup_env;

	index = ft_get_var_index(var, env);
	if (index == -1)
	{
		ft_add_var_to_env(var, value, shell);
		return ;
	}
	res = ft_safe_malloc(ft_get_str_length(var, value) + 2);
	i = 0;
	while (var[i])
	{
		res[i] = var[i];
		i++;
	}
	j = 0;
	res[i++] = '=';
	while (value[j])
		res[i++] = value[j++];
	res[i] = '\0';
	free(env[index]);
	env[index] = res;
}

char	*ft_get_var_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	res = ft_safe_malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
