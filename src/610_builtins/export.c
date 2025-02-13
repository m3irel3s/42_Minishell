/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 10:59:03 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

	// valid names - Must start with a letter or '_', and contain only letters or numbers ######
	// print export ####
	// add new variable 
	// if it exists, overwrite, if it is "+=" append
	// if doenst exist, give empty value if nothing has been assigned 

	// 0 no quote
	// 1 single quote
	// 2 double quote
static void	ft_free_export(char **export);

void	ft_export(t_shell *shell)
{
	t_token	*curr;
	char	**export = NULL;

	curr = shell->tokens;
	if (!curr->next)
	{
		export = ft_duplicate_env(shell->dup_env);
		export = ft_sort_export(export);
		ft_print_export(export);
		ft_free_export(export);
		return ;
	}
	while (curr->next)
	{
		char	*var;
		char	*value;
		curr = curr->next;
		if(ft_check_var_chars(curr->value) == SUCCESS)
			ft_printf(1, "Chars ok\n");
		var = ft_get_var_name(curr->value);
		printf("var=> %s\n", var);
		value = curr->value + (ft_strlen(var) + 1);
		printf("value=> %s\n", value);
		ft_set_var_value(var, value, shell);
	}
	return;
}

static void	ft_free_export(char **export)
{
	int		i = 0;
	char	*to_free;

	while (export[i])
	{
		to_free = export[i];
		i++;
		free(to_free);
	}
	free(export);
}


