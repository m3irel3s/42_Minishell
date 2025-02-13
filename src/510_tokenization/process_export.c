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

static t_status	ft_process_export_assign(t_shell *shell, char *word,
					char *equal_sign);
static t_status	ft_process_export_no_assign(t_shell *shell, char *word);
static t_status	ft_create_name_token(t_shell *shell, char **var_name, char *word);
static t_status	ft_create_equal_token(t_shell *shell);

/**
 * @brief Processes the assignment part of the export command.
 *
 * Extracts variable name and value, handles quotes, and adds to env.
 *
 * @param shell A pointer to the shell structure.
 * @param word The input string to be processed.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
t_status	ft_process_export_assignment(t_shell *shell, char *word)
{
	char	*equal_sign;

	equal_sign = ft_strchr(word, '=');
	if (equal_sign != NULL)
		return (ft_process_export_assign(shell, word, equal_sign));
	else
		return (ft_process_export_no_assign(shell, word));
}

/**
 * @brief create the token and add to the list
 *
 * @param shell A pointer to the shell structure.
 * @param var_name The pointer to var name
 * @param word The input string to be processed.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status ft_create_name_token(t_shell *shell, char **var_name, char *word)
{
	t_token *token_var_name;

	if (!ft_is_valid_variable_name(*var_name))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(word, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(*var_name);
		return (ERROR);
	}
	token_var_name = ft_create_token(*var_name, WORD);
	if (!token_var_name)
		return (ERROR);
	ft_add_token_to_list(shell, token_var_name);
	return (SUCCESS);
}

/**
 * @brief create the token and add to the list
 *
 * @param shell A pointer to the shell structure.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_create_equal_token(t_shell *shell)
{
	t_token *token_equal;

	token_equal = ft_create_token("=", EQUAL);
	if (!token_equal)
		return (ERROR);
	ft_add_token_to_list(shell, token_equal);
	return (SUCCESS);
}

/**
 * @brief Handles the case where there is an assignment in export.
 *
 * @param shell A pointer to the shell structure.
 * @param word The input string to be processed.
 * @param equal_sign A pointer to the equal sign.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_process_export_assign(t_shell *shell, char *word,
					char *equal_sign)
{
	char *var_name;
	char *var_value;

	var_name = ft_substr(word, 0, equal_sign - word);
	if (!var_name)
		return (ERROR);
	if (ft_create_name_token(shell, &var_name, word) == ERROR)
		return (ERROR);
	if (ft_create_equal_token(shell) == ERROR)
		return (ERROR);
	var_value = ft_strdup(equal_sign + 1);
	if (!var_value)
	{
		free(var_name);
		return (ERROR);
	}
	free(var_name);
	return (ft_handle_export_value(shell, var_value));
}

/**
 * @brief Handles the case where there is NO assignment in export.
 *
 * @param shell A pointer to the shell structure.
 * @param word The input string to be processed.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_process_export_no_assign(t_shell *shell, char *word)
{
	t_token	*token_var_name;

	if (!ft_is_valid_variable_name(word))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(word, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (ERROR);
	}
	token_var_name = ft_create_token(word, WORD);
	if (!token_var_name)
		return (ERROR);
	ft_add_token_to_list(shell, token_var_name);
	return (SUCCESS);
}
