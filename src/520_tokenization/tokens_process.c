/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 11:25:41 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status	ft_process_token(t_shell *shell, char *token_str);

/**
 * @brief Tokenizes the input string in the shell structure.
 *
 * This function splits the input string into tokens and adds them to the
 * shell's token list. It handles quoted strings and ensures that quotes are
 * properly matched.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param split_input A 2D array of strings, where each string is a token of the
 * input string.
 * @return SUCCESS if the input is tokenized successfully, or an error status if
 * there is a memory allocation failure or unmatched quotes.
 */
t_status	ft_tokenize(t_shell *shell, char **split_input)
{
	int	i;

	if (!shell || !split_input)
		return (ft_print_error(ERR_INVALID_PARAMS));
	i = 0;
	while (split_input[i])
	{
		if (ft_process_token(shell, split_input[i]) != SUCCESS)
			return (ft_print_error(ERR_TOKENIZATION_FAIL));
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Processes a single token.
 *
 * This function determines if the token is quoted and, if it is, removes the
 * quotes. It then creates a new token structure and adds it to the shell's
 * token list.
 *
 * @param shell The shell structure containing the token list.
 * @param token_str The string containing the token value.
 * @return SUCCESS if the token is processed successfully, or an error code.
 */
static t_status	ft_process_token(t_shell *shell, char *token_str)
{
	size_t		len;
	int			quoted;
	t_status	status;

	if (!token_str)
		return (ft_print_error(ERR_NULL_TOKEN_VALUE));
	len = ft_strlen(token_str);
	quoted = 0;
	if (len >= 2)
	{
		if (token_str[0] == '\'' && token_str[len - 1] == '\'')
			quoted = 1;
		else if (token_str[0] == '"' && token_str[len - 1] == '"')
			quoted = 2;
	}
	status = ft_create_and_add_token(shell, token_str, ft_strlen(token_str), quoted);
	// return (ft_create_and_add_token(shell, token_str, ft_strlen(token_str),
			// quoted));
	return status;
	
}
