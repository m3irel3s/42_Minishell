/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/13 22:06:37 by meferraz         ###   ########.fr       */
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
		t_token *curr = shell->tokens;
		char    **export = NULL;
		char    *var_name;
		char    *var_value;
		char    *equal_sign;

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
			default:
				printf("UNKNOWN");
				break;
		}
		printf("\n");
		curr = curr->next;
	}
	curr = shell->tokens;
	// Handle 'export' without arguments
	if (!curr->next)
	{
		export = ft_duplicate_env(shell->dup_env);
		export = ft_sort_export(export);
		ft_print_export(export);
		ft_free_arr(export);
		return;
	}

	// Skip 'export' command token
	if (curr && ft_strcmp(curr->value, "export") == 0)
		curr = curr->next;

	while (curr && curr->type == WORD)
	{
		char *assignment = curr->value;

		// Validate variable name syntax
		if (ft_check_var_chars(assignment) != SUCCESS)
		{
			ft_printf(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", assignment);
			curr = curr->next;
			continue;
		}

		equal_sign = ft_strchr(assignment, '=');

		if (equal_sign) {
			// Split into variable and value
			*equal_sign = '\0';
			var_name = assignment;
			var_value = equal_sign + 1;

			// Remove surrounding quotes if present
			if (*var_value == '"' || *var_value == '\'') {
				char quote = *var_value;
				var_value++;
				size_t len = ft_strlen(var_value);
				if (len > 0 && var_value[len-1] == quote)
					var_value[len-1] = '\0';
			}

			ft_set_var_value(var_name, var_value, shell);
			*equal_sign = '='; // Restore original string
		}
		else {
			// Handle export without value
			ft_set_var_value(assignment, "", shell);
		}

		curr = curr->next;
	}
}

