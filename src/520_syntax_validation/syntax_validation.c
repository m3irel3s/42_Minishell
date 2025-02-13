/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/13 14:32:05 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_handle_pipe_error(t_token_type prev, t_token *current);
static t_status	ft_handle_redirection_error(t_token *current);
static t_status	ft_handle_consecutive_redirections(t_token_type prev,
					t_token_type type, char *value);
static t_status	ft_check_end_of_input(t_token_type prev);
extern t_status ft_check_consecutive_operators(t_token *token);
extern t_status ft_check_heredoc(t_token *token);

/**
* @brief Validates the syntax of a linked list of tokens.
*
* This function takes a linked list of tokens and checks for various syntax errors,
* including the use of pipes, redirection operators, consecutive operators, and
* here-document syntax. If any syntax errors are found, the function returns ERROR.
* If all syntax checks succeed, the function returns SUCCESS.
*
* @param tokens A pointer to the linked list of tokens.
*
* @return Returns SUCCESS if the syntax is valid; otherwise, returns ERROR.
*/
t_status	ft_validate_syntax(t_token *tokens)
{
	t_token			*current;
	t_token_type	prev;
	t_token_type	type;

	current = tokens;
	prev = 666;
	while (current)
	{
		type = current->type;
		if (type == PIPE && ft_handle_pipe_error(prev, current) == ERROR)
			return (ERROR);
		if ((type == REDIRECT_IN || type == REDIRECT_OUT
				|| type == HEREDOC || type == REDIRECT_APPEND)
			&& ft_handle_redirection_error(current) == ERROR)
			return (ERROR);
		if (ft_handle_consecutive_redirections(prev, type, current->value) == ERROR)
			return (ERROR);
		prev = type;
		current = current->next;
	}
	if (ft_check_end_of_input(prev) == ERROR)
		return (ERROR);
	if (ft_check_consecutive_operators(tokens) == ERROR)
		return (ERROR);
	if (ft_check_heredoc(tokens) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/**
* @brief Handles pipe errors in a linked list of tokens.
*
* This function checks if the | operator is used correctly in a linked
* list of tokens. If the | operator is used as the first token, or if it
* is used after or before a redirection operator, or if it is the last
* token in the linked list, the function returns ERROR. If the | operator
* is used correctly, the function returns SUCCESS.
*
* @param prev The type of the previous token.
* @param current A pointer to the current token.
*
* @return Returns SUCCESS if the | operator is used correctly;
*         otherwise, returns ERROR.
*/
static t_status	ft_handle_pipe_error(t_token_type prev, t_token *current)
{
	if (prev == 666 || prev == PIPE || prev == REDIRECT_IN
		|| prev == REDIRECT_OUT || prev == HEREDOC
		|| prev == REDIRECT_APPEND || !current->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
* @brief Handles redirection errors in a linked list of tokens.
*
* This function checks if the redirection operators are used correctly in a
* linked list of tokens. If a redirection operator is used as the last token,
* or if it is used before a redirection operator, or if it is used after a
* pipe, the function returns ERROR. If a redirection operator is used correctly,
* the function returns SUCCESS.
*
* @param current A pointer to the current token.
*
* @return Returns SUCCESS if the redirection operator is used correctly;
*         otherwise, returns ERROR.
*/
static t_status	ft_handle_redirection_error(t_token *current)
{
	if (!current->next || current->next->type == PIPE
		|| current->next->type == REDIRECT_IN
		|| current->next->type == REDIRECT_OUT
		|| current->next->type == HEREDOC
		|| current->next->type == REDIRECT_APPEND)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		if (current->next)
			ft_putstr_fd(current->next->value, STDERR_FILENO);
		else
			ft_putstr_fd("newline", STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
* @brief Checks for consecutive redirection operators in a linked
* list of tokens.
*
* This function takes the type of the previous token and the current token,
* as well as the value of the current token. If the current token is a
* redirection operator and the previous token is also a redirection operator,
* the function returns ERROR. If the current token is a redirection operator
* and the previous token is not a redirection operator, the function returns
* SUCCESS.
*
* @param prev The type of the previous token.
* @param type The type of the current token.
* @param value The value of the current token.
*
* @return Returns SUCCESS if the redirection operators are used correctly;
*         otherwise, returns ERROR.
*/
static t_status	ft_handle_consecutive_redirections(t_token_type prev,
	t_token_type type, char *value)
{
	if ((type == REDIRECT_IN || type == REDIRECT_OUT
			|| type == HEREDOC || type == REDIRECT_APPEND)
		&& (prev == REDIRECT_IN || prev == REDIRECT_OUT
			|| prev == HEREDOC || prev == REDIRECT_APPEND))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
* @brief Checks for syntax errors at the end of the input.
*
* This function verifies if the last token in the input is a pipe
* or a redirection operator. If so, it indicates a syntax error
* due to an unexpected end of file. The function returns ERROR
* in such cases, otherwise, it returns SUCCESS.
*
* @param prev The type of the last token processed.
*
* @return Returns SUCCESS if the input ends correctly; otherwise,
*         returns ERROR.
*/
static t_status	ft_check_end_of_input(t_token_type prev)
{
	if (prev == PIPE || prev == REDIRECT_IN || prev == REDIRECT_OUT
		|| prev == HEREDOC || prev == REDIRECT_APPEND)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
			STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}
