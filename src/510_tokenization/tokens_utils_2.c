/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:26:26 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 12:00:15 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		ft_add_token_to_shell(t_shell *shell, t_token *new_token);
static void		ft_remove_quotes(char *str);
static t_status	ft_is_last_token_heredoc(t_shell *shell);

/**
 * @brief Creates a new token from a given value and adds it to the token list.
 *
 * Allocates a new token structure, duplicates the token string using
 * ft_safe_strndup, determines its type, and appends it to the shell's token
 * list.
 *
 * @param shell The shell structure containing the token list.
 * @param value The token string.
 * @param len The length of the token string.
 * @param quoted Indicates if the token was quoted (1 for quoted, 0 otherwise).
 * @return SUCCESS if the token is created and added successfully, or an
 * error code.
 */
t_status	ft_create_and_add_token(t_shell *shell, char *value, size_t len, int quoted)
{
	t_token	*new_token;

	if (!value || len == 0)
		return (SUCCESS);
	new_token = ft_safe_malloc(sizeof(t_token));
	if (!new_token)
		return (ft_print_error(ERR_TOKEN_CREATION_FAIL));
	new_token->val.og_value = ft_safe_strndup(value, len);
	if (!new_token->val.og_value)
	{
		ft_free(new_token);
		return (ft_print_error(ERR_TOKEN_CREATION_FAIL));
	}
	new_token->val.value = ft_safe_strdup(new_token->val.og_value);
	if (ft_is_last_token_heredoc(shell) != SUCCESS)
		new_token->val.value = ft_expand(shell, new_token->val.value);
	if (!new_token->val.value || ft_strlen(new_token->val.value) == 0)
	{
		ft_free(new_token->val.value);
		ft_free(new_token->val.og_value);
		ft_free(new_token);
		return (SUCCESS);
	}
	ft_remove_quotes(new_token->val.value);
	if (!new_token->val.value)
	{
		ft_free(new_token->val.value);
		ft_free(new_token);
		return (ft_print_error(ERR_TOKEN_CREATION_FAIL));
	}
	new_token->type = ft_determine_token_type(new_token->val.og_value, new_token->val.value, len);
	new_token->quoted = quoted;
	new_token->next = NULL;
	new_token->prev = NULL;
	ft_add_token_to_shell(shell, new_token);
	return (SUCCESS);
}

/**
 * @brief Checks if the last token in the shell's token list is a heredoc token.
 *
 * Iterates through the token list until the last token is reached and checks
 * its type. If it is a heredoc token, the function returns SUCCESS. Otherwise,
 * it returns ERROR.
 *
 * @param shell The shell structure containing the token list.
 * @return SUCCESS if the last token is a heredoc token, ERROR otherwise.
 */
static t_status ft_is_last_token_heredoc(t_shell *shell)
{
	t_token	*token;

	token = shell->tokens;
	if (!token)
		return (ERROR);
	while (token->next)
		token = token->next;
	if (token->type == HEREDOC)
		return (SUCCESS);
	return (ERROR);
}

/**
 * @brief Appends a new token to the end of the shell's token list.
 *
 * If the token list is empty, the new token becomes the first token.
 * Otherwise, the function iterates to the end of the list and appends the
 * new token.
 *
 * @param shell The shell structure containing the token list.
 * @param new_token The token to be appended.
 */
static void	ft_add_token_to_shell(t_shell *shell, t_token *new_token)
{
	t_token	*last_token;

	if (!shell->tokens)
		shell->tokens = new_token;
	else
	{
		last_token = shell->tokens;
		while (last_token->next)
			last_token = last_token->next;
		last_token->next = new_token;
		new_token->prev = last_token;
	}
}

/**
 * @brief Removes quotes from a given string in place.
 *
 * This function iterates through the input string and removes any single or
 * double quotes, while preserving the rest of the characters. It handles both
 * single and double quotes, ensuring that quoted sections are processed
 * correctly. The string is modified in place, and only the non-quoted
 * characters are retained.
 *
 * @param str The string from which quotes are to be removed.
 */
static void	ft_remove_quotes(char *str)
{
	int		read;
	int		write;
	int		in_quotes;
	char	quote_char;

	read = 0;
	write = 0;
	in_quotes = 0;
	while (str[read])
	{
		if ((str[read] == '\'' || str[read] == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = str[read++];
		}
		else if (in_quotes && str[read] == quote_char)
		{
			in_quotes = 0;
			read++;
		}
		else
			str[write++] = str[read++];
	}
	str[write] = '\0';
}
