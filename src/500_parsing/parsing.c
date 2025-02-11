/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 12:02:14 by meferraz         ###   ########.fr       */
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
	if (ft_tokenize(shell) != SUCCESS)
		return (ERROR);
	t_token *current = shell->tokens;
	while (current)
	{
		printf("this is token: %s, type: ", current->value);
		switch (current->type)
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
		current = current->next;
	}
	current = shell->tokens;
	while (current)
	{
		if (ft_validate_syntax(current) != SUCCESS)
			return (ERROR);
		current = current->next;
	}
	return (SUCCESS);
}
