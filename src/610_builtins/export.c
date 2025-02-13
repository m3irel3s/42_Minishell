/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 15:30:07 by jmeirele         ###   ########.fr       */
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

void	ft_export(t_shell *shell)
{
	t_token	*curr;
	char	**export = NULL;

	curr = shell->tokens;
	if (!curr->next->next)
	{
		export = ft_duplicate_env(shell->dup_env);
		export = ft_sort_export(export);
		ft_print_export(export);
		ft_free_arr(export);
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



