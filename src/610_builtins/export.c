/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 17:27:39 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static char	**ft_store_export(t_shell *shell);
void	ft_export(t_shell *shell)
{
	char	**env = shell->dup_env;
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (env[j])
	{
		i = 0;
		while (env[i + 1])
		{
			if (ft_strcmp(ft_get_var_name(env[i]), ft_get_var_name(env[i + 1])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", ft_get_var_name(env[i]));
		i++;
	}
	return;
}


// static char	**ft_store_export(t_shell *shell)
// {
// 	int i = 0;
// 	char	**env;
// 	char	*res;

// 	env = shell->dup_env;
// 	while (env[i])
// 	{
// 		res = ft_strdup("declare -x ");
// 		res = ft_strjoin_gnl(res, ft_get_var_name(env[i]));
// 		res = ft_strjoin_gnl(res, "=\"");
// 		res = ft_strjoin_gnl(res, ft_get_env_value(ft_get_var_name(env[i]), env));
// 		res = ft_strjoin_gnl(res, "\"");
// 		printf("%s\n", res);
// 		i++;
// 		free(res);
// 	}
// 	return ;
// }
