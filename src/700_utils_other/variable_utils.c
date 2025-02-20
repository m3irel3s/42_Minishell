/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:40:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 15:12:52 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_get_str_length(char *str1, char *str2)
{
	return (ft_strlen(str1) + ft_strlen(str2));
}

char	*ft_get_var_value(char *var, char **env)
{
	int		i;
	char	*to_compare;

	i = 0;
	while (env[i])
	{
		to_compare = ft_get_var_name(env[i]);
		if (ft_strcmp(to_compare, var) == SUCCESS)
			return (ft_free(to_compare), env[i] + ft_strlen(var) + 1);
		i++;
		ft_free(to_compare);
	}
	return (NULL);
}

int	ft_get_var_index(char *var, char **env)
{
	int		i;
	char	*to_compare;

	i = 0;
	while (env[i])
	{
		to_compare = ft_get_var_name(env[i]);
		if (ft_strcmp(to_compare, var) == SUCCESS)
			return (ft_free(to_compare), i);
		i++;
		ft_free(to_compare);
	}
	return (-1);
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


