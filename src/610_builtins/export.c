/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 17:27:38 by meferraz         ###   ########.fr       */
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
	while (curr)
	{
		printf("this is token: %s, type: ", curr->value);
		switch (curr->type)
		{
			case WORD:
				printf("WORD");
				break;
			case PIPE:
				printf("PIPE");
				break;
			case REDIRECT_IN:
				printf("REDIRECT_IN");
				break;
			case REDIRECT_OUT:
				printf("REDIRECT_OUT");
				break;
			case REDIRECT_APPEND:
				printf("REDIRECT_APPEND");
				break;
			case HEREDOC:
				printf("HEREDOC");
				break;
			case EQUAL:
				printf("EQUAL");
				break;
			default:
				printf("UNKNOWN");
				break;
		}
		printf("\n");
		curr = curr->next;
	}
	curr = shell->tokens;
	if (!curr->next)
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
		if(ft_check_var_chars(curr->value) == SUCCESS)
			ft_printf(1, "Chars ok\n");
		var = ft_get_var_name(curr->value);
		printf("var=> %s\n", var);
		value = curr->value + (ft_strlen(var) + 1);
		printf("value=> %s\n", value);
		ft_set_var_value(var, value, shell);
		curr = curr->next;
	}
	return;
}



