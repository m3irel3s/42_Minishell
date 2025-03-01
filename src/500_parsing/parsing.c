/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (ft_validate_syntax(shell->input) != SUCCESS)
		return (ERROR);
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
