/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:51 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/13 14:53:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_add_tokens(t_shell *shell, char *var_name, char *var_value);

/**
 * @brief Processes an export assignment in the shell input.
 *
 * This function parses a word to determine if it contains an export
 * assignment in the form of "var_name=var_value". If the assignment
 * is present, it validates the variable name and creates tokens for
 * the variable name, the "=" operator, and the variable value. If no
 * "=" is found, it creates a token for the word as a variable name
 * with no value. The tokens are added to the shell's token list.
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @param word A pointer to the string representing the potential export assignment.
 *
 * @return Returns SUCCESS if the tokens are successfully created and added;
 *         otherwise, returns ERROR if memory allocation fails or if the
 *         variable name is invalid.
 */

t_status	ft_process_export_assignment(t_shell *shell, char *word)
{
	char	*equals;
	char	*var_name;
	char	*var_value;

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
		return (ft_add_tokens(shell, var_name, var_value));
	}
	return (ft_add_tokens(shell, word, ""));
}

/**
 * @brief Adds tokens to the shell's token list, representing an export
 *        assignment.
 *
 * This function creates tokens for the variable name, the "=" operator,
 * and the variable value (if any). It appends these tokens to the end
 * of the shell's token list.
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @param var_name A pointer to the string containing the variable name.
 * @param var_value A pointer to the string containing the variable value,
 *                  or an empty string if the variable has no value.
 *
 * @return A status code indicating the success of the operation.
 *
 * @retval ERROR if memory allocation fails.
 * @retval SUCCESS otherwise.
 */
static t_status	ft_add_tokens(t_shell *shell, char *var_name, char *var_value)
{
	t_token	*new_token;

	new_token = ft_create_token(var_name, WORD);
	if (!new_token)
		return (ERROR);
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
	return (SUCCESS);
}
