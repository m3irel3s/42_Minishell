/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:02 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/14 17:42:16 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_swap(char **export, int i);

/**
 * Prints the list of exported variables and their values.
 *
 * @param shell The minishell state.
 *
 * @note This function prints the list of exported variables and their values
 * according to the POSIX standard for the export command.
 *
 * @note This function does not handle any errors.
 */
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

/**
 * Swaps the elements of the export array at indices i and i + 1 if the
 * variable name at index i is lexicographically greater than the variable name
 * at index i + 1.
 *
 * @param export The array of exported variables.
 * @param i The index at which to perform the swap.
 *
 * @note This function does not handle any errors.
 */
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

/**
 * Outputs the list of exported variables in a specific format.
 *
 * This function iterates over the provided array of exported variables and
 * prints each variable in the format "declare - x var=\"value\"" if the
 * variable has an associated value, or "declare - x var" if it does not.
 * The output is consistent with the POSIX standard for the export command.
 *
 * @param export The array of exported variables.
 *
 * @note This function does not handle any errors.
 */

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
		else if (eq_sign)
			ft_printf(1, "declare - x %s=\"%s\"\n", var, value);
		ft_free(var);
		i++;
	}
}
