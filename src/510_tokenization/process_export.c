/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:51 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/12 22:10:59 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processes an export assignment.
 *
 * Checks if the given word is a valid variable name and processes it
 * accordingly. If the word contains an equals sign, it is split into a variable
 * name and value. The variable name is checked to ensure it is a valid
 * identifier. If it is, a new token is created and added to the shell's token
 * list.
 *
 * @param shell A pointer to the shell structure.
 * @param word The word to process.
 *
 * @return Returns SUCCESS if the word is successfully processed, ERROR
 *         otherwise.
 */
t_status ft_process_export_assignment(t_shell *shell, char *word)
{
	char	*equals;
	char	*var_name;
	char	*var_value;
	t_token	*new_token;

	equals = ft_strchr(word, '=');
	if (equals)
	{
		*equals = '\0';
		var_name = word;
		var_value = equals + 1;
		if (!ft_isalpha(*var_name) && *var_name != '_')
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", STDERR_FILENO);
			return (ERROR);
		}
		new_token = ft_create_token(var_name, WORD);
		ft_add_token_to_list(shell, new_token);
		new_token = ft_create_token("=", EQUAL);
		if (!new_token)
			return (ERROR);
		ft_add_token_to_list(shell, new_token);
		if (*var_value)
		{
			new_token = ft_create_token(var_value, WORD);
			if (!new_token)
				return (ERROR);
			ft_add_token_to_list(shell, new_token);
		}
		*equals = '=';
	}
	else
	{
		new_token = ft_create_token(word, WORD);
		ft_add_token_to_list(shell, new_token);
	}
	return (SUCCESS);
}
