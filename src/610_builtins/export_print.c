/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:02 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/17 16:52:18 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_sort_export(char **export)
{
	int		i;
	int		j;
	char	*temp;
	char	*var_name1;
	char	*var_name2;

	j = 0;
	while (export[j])
	{
		i = 0;
		while (export[i + 1])
		{
			var_name1 = ft_get_var_name(export[i]);
			var_name2 = ft_get_var_name(export[i + 1]);
			if (ft_strcmp(var_name1, var_name2) > 0)
			{
				temp = export[i];
				export[i] = export[i + 1];
				export[i + 1] = temp;
			}
			free(var_name1);
			free(var_name2);
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
		free(var);
		i++;
	}
}
