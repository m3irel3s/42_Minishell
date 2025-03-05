/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:02 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/05 17:40:23 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_swap(char **export, int i);

void	ft_print_export(t_shell *shell)
{
	char	**export;

	export = NULL;
	export = ft_duplicate_env(shell->env_cpy);
	export = ft_sort_export(export);
	ft_output_export(export);
	ft_free_arr(export);
	return ;
}

char	**ft_sort_export(char **export)
{
	int		i;
	int		j;

	j = 0;
	while (export[j])
	{
		i = 0;
		while (export[i + 1])
		{
			ft_swap(export, i);
			i++;
		}
		j++;
	}
	return (export);
}

static void	ft_swap(char **export, int i)
{
	char	*temp;
	char	*var_name1;
	char	*var_name2;

	var_name1 = ft_get_var_name(export[i]);
	var_name2 = ft_get_var_name(export[i + 1]);
	if (ft_strcmp(var_name1, var_name2) > 0)
	{
		temp = export[i];
		export[i] = export[i + 1];
		export[i + 1] = temp;
	}
	ft_free(var_name1);
	ft_free(var_name2);
}

void	ft_output_export(char **export)
{
	char	*res;
	char	*var;
	char	*value;
	char	*eq_sign;
	int		i;

	i = 0;
	while (export[i])
	{
		res = export[i];
		var = ft_get_var_name(res);
		value = ft_get_var_value(var, export);
		eq_sign = ft_strchr(export[i], '=');
		if (eq_sign && ft_strcmp(value, "") == 0)
			ft_printf(1, "declare - x %s=\"\"\n", var);
		else if (ft_strcmp(value, "") == 0)
			ft_printf(1, "declare - x %s\n", var);
		else
			ft_printf(1, "declare - x %s=\"%s\"\n", var, value);
		ft_free(var);
		i++;
	}
}
