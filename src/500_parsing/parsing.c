/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 14:20:45 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_validate_all_tokens(t_shell *shell);

/**
 * @brief Parses the input string of the shell, tokenizing it, validating its
 * syntax, expanding variables, and setting up redirections.
 *
 * @param shell A pointer to the shell structure containing the input string.
 *
 * @return Returns SUCCESS if the input is successfully parsed; otherwise,
 * returns ERROR.
 */
t_status	ft_parse_input(t_shell *shell)
{
	if (ft_tokenize(shell) != SUCCESS)
	{
		ft_printf(STDERR_FILENO, ERR_TOKENIZATION_FAIL);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	if (ft_validate_all_tokens(shell) != SUCCESS)
	{
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	if (ft_expand(shell) != SUCCESS)
	{
		ft_printf(STDERR_FILENO, ERR_EXPANSION_FAIL);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	shell->exit_status = EXIT_SUCCESS;
	return (SUCCESS);
}

/**
 * @brief Validates the syntax of all tokens in the shell structure.
 *
 * @param shell A pointer to the shell structure containing the tokens.
 *
 * @return Returns SUCCESS if all tokens have valid syntax; otherwise,
 * returns ERROR.
 */
static t_status	ft_validate_all_tokens(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (ft_validate_syntax(current) != SUCCESS)
		{
			ft_printf(STDERR_FILENO, ERR_SYNTAX_VALIDATION_FAIL);
			return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
