/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/14 11:12:56 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/**
 * @brief Parses the input string of the shell, tokenizing it, validating its syntax,
 *        expanding variables, and setting up redirections.
 *
 * This function first tokenizes the input string stored in the shell structure.
 * If tokenization fails, it returns ERROR. It then iterates through the tokens
 * to validate their syntax, returning ERROR if any invalid syntax is found.
 * Upon successful validation, it expands any variables present in the tokens
 * and creates a list of redirections. The function returns SUCCESS if all
 * operations complete without errors.
 *
 * @param shell A pointer to the shell structure containing the input string.
 *
 * @return Returns SUCCESS if the input is successfully parsed; otherwise, returns ERROR.
 */

int	ft_parse_input(t_shell *shell)
{
	t_token	*current;

	if (ft_tokenize(shell) != SUCCESS)
		return (ERROR);
	current = shell->tokens;
	// while (current)
	// {
	// 	if (ft_validate_syntax(current) != SUCCESS)
	// 		return (ERROR);
	// 	current = current->next;
	// }
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
	ft_expand_tokens(shell);
	current = shell->tokens;
	//ft_create_redirection_list(shell);
	return (SUCCESS);
}
	/*while (current)
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
	current = shell->tokens;*/

