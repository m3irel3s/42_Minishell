/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 13:40:34 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


	// valid names - Must start with a letter or '_', and contain only letters or numbers ######
	// print export ####
	// add new variable 
	// if it exists, overwrite, if it is "+=" append
	// if doenst exist, give empty value if nothing has been assigned 
void	ft_export(t_shell *shell)
{
	t_token *curr;

	curr = shell->tokens;
	if (!curr->next)
	{
		char	**export = ft_duplicate_env(shell->dup_env);
		export = ft_sort_export(export);
		ft_print_export(export);
		return ;
	}
	while (curr->next)
	{
		curr = curr->next;
		if(ft_check_var_chars(curr->value) == SUCCESS)
			ft_printf(1, "Chars ok");
		else
			ft_printf(1, "Chars wrong");
	}
	return;
}


