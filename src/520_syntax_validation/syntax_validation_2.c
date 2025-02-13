/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/13 14:33:41 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
* @brief Checks for consecutive operators in the token list.
*
* This function ensures that consecutive pipes (||) or redirection operators
* (>>, etc.) are not present, which would be a syntax error in shell scripting.
*
* @param token The head of the token list to check.
*
* @return Returns SUCCESS if no consecutive operators are found; otherwise,
*         returns ERROR.
*/
t_status	ft_check_consecutive_operators(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			return (ERROR);
		}
		if ((token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
			&& token->next && (token->next->type == REDIRECT_OUT || token->next->type == REDIRECT_APPEND))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
			ft_putstr_fd(token->next->value, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
}

/**
* @brief Verifies the syntax for here-document in the token list.
*
* This function checks if a here-document (<<) is correctly used with a following
* word for the delimiter.
*
* @param token The head of the token list to check.
*
* @return Returns SUCCESS if here-document syntax is correct; otherwise,
*         returns ERROR.
*/
t_status	ft_check_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC && (!token->next || token->next->type != WORD))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			return (ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
}
