/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:40:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 16:22:40 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_increment_env_size(t_shell *shell, char *var, char *value);
static char	*ft_add_var(char *var, char *value);

void	ft_add_var_to_env(char *var, char *value, t_shell *shell)
{
	(void)var;
	(void)value;
	ft_increment_env_size(shell, var, value);
}

int	ft_get_env_size(t_shell *shell)
{
	int		i;
	char	**env;

	env = shell->dup_env;
	i = 0;
	if (!env)
		return (-1);
	while (env[i])
		i++;
	return (i);
}

int	ft_get_str_length(char *str1, char *str2)
{
	return (ft_strlen(str1) + ft_strlen(str2));
}

static void	ft_increment_env_size(t_shell *shell, char *var, char *value)
{
	char	**new_env;
	char	**old_env;
	int		new_size;
	int		i;
	
	old_env = shell->dup_env;
	i = 0;
	new_size = ft_get_env_size(shell) + 1;
	new_env = ft_safe_malloc(sizeof(char *) * new_size);
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	new_env[i] = ft_add_var(var, value);
	printf("i => %d\n",i);
	printf("new_size => %d\n",new_size);
	shell->dup_env = new_env;
}

static char	*ft_add_var(char *var, char *value)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	res = ft_safe_malloc(ft_get_str_length(var, value) + 2);
	while (var[i])
	{
		res[i] = var[i];
		i++;
	}
	res[i] = '=';
	j = 0;
	while (value[j])
		res[i++] = value[j++];
	res[i] = '\0';
	return res;
}






