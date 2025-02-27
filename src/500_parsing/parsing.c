/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 09:06:34 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_validate_all_tokens(t_shell *shell);

/**
 * @brief Parses the input string in the shell structure.
 *
 * This function expands the input string, splits it into tokens, creates token
 * structures, and validates the tokens.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @return SUCCESS if the input is parsed successfully, or an error status if
 * there is a failure during any step.
 */
t_status	ft_parse_input(t_shell *shell)
{
	char	**split_input;

	if (!shell || !shell->input)
		return (ft_print_error(ERR_INVALID_SHELL_OR_INPUT));
	if (ft_validate_syntax(shell) != SUCCESS)
		return (ft_print_error(ERR_SYNTAX_VALIDATION_FAIL));
	if (ft_expand(shell) != SUCCESS)
		return (ft_print_error(ERR_EXPANSION_FAIL));
	split_input = ft_split_input(shell->input);
	if (!split_input)
		return (ft_print_error(ERR_TOKENIZATION_FAIL));
	if (ft_tokenize(shell, split_input) != SUCCESS)
	{
		ft_free_arr(split_input);
		return (ft_print_error(ERR_TOKENIZATION_FAIL));
	}
	ft_free_arr(split_input);
	g_exit_status = EXIT_SUCCESS;
	return (SUCCESS);
}

/**
 * @brief Validates the syntax of all tokens in the shell structure.
 *
 * Iterates through the token list and validates the syntax of each token.
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
			ft_print_error(ERR_SYNTAX_VALIDATION_FAIL);
			return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
