/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 11:39:18 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Parses the input entered by the user in the shell.
 *
 * This function initializes the shell's parser structure and attempts
 * to tokenize the input stored in the shell structure. It uses safe
 * memory allocation for the parser and sets its initial state. If
 * tokenization is successful, the function returns SUCCESS; otherwise,
 * it returns ERROR. The function is prepared to validate syntax, but
 * the validation logic is currently commented out.
 *
 * @param shell A pointer to the shell structure containing the input
 *              to be parsed and the parser state to be initialized.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
 */

int	ft_parse_input(t_shell *shell)
{
	shell->parser = ft_safe_malloc(sizeof(t_parser));
	shell->parser = (t_parser){STATE_GENERAL, NO_QUOTE, 0, 0, 0};
	if (ft_tokenize(shell) != SUCCESS)
		return (ERROR);
	/*if (ft_validate_syntax(shell) != SUCCESS)
	{
		perror("Error syntax!");
		return (ERROR);
	}*/
	return (SUCCESS);
}
