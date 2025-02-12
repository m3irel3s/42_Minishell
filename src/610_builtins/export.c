/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 11:03:53 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_print_export(char **export);
static char	**ft_sort_export(char **export);

void	ft_export(t_shell *shell)
{
	char	**export = ft_duplicate_env(shell->dup_env);
	export = ft_sort_export(export);
	ft_print_export(export);
	return;
}

static char	**ft_sort_export(char **export)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (export[j])
	{
		i = 0;
		while (export[i + 1])
		{
			if (ft_strcmp(ft_get_var_name(export[i]), ft_get_var_name(export[i + 1])) > 0)
			{
				temp = export[i];
				export[i] = export[i + 1];
				export[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
	return export;
}

static void	ft_print_export(char **export)
{
	int i = 0;
	while (export[i])
	{
		char	*res = export[i];
		char	*var_name = ft_get_var_name(res);
		char	*value = ft_get_env_value(var_name, export);
		ft_printf(1, "declare - x %s=\"%s\"\n", var_name, value);
		i++;
	}
	free(export);
}
