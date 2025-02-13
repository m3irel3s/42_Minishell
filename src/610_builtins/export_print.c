/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:02 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 10:28:16 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_sort_export(char **export)
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
	return (export);
}

void	ft_print_export(char **export)
{
	char	*res;
	char	*var;
	char	*value;
	int		i;

	i = 0;
	while (export[i])
	{
		res = export[i];
		var = ft_get_var_name(res);
		value = ft_get_var_value(var, export);
		ft_printf(1, "declare - x %s=\"%s\"\n", var, value);
		i++;
	}
}
