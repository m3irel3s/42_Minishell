/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:15:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 10:50:12 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Expand variables in a heredoc input line.
 *
 * This function takes a line read from the standard input and a pointer to
 * the shell structure, and expands any variables it finds. It returns a new
 * string with the variables expanded.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param line The input line from the heredoc that may contain variables
 * to be expanded.
 * @return A new string with the variables expanded, or NULL if memory
 * allocation fails.
 */
char	*ft_expanded_line(t_shell *shell, char *line)
{
	char	*expanded;
	char	*tmp;
	size_t	i;

	expanded = ft_safe_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = ft_handle_dollar(shell, line, &i);
			if (tmp)
			{
				expanded = ft_safe_strjoin(expanded, tmp, 0);
				free(tmp);
			}
		}
		else
			expanded = ft_process_char(expanded, line[i++]);
	}
	ft_free(line);
	return (expanded);
}

/**
 * @brief Process heredoc delimiter and update tokens.
 *
 * This function takes a token pointing to the heredoc delimiter, and a string
 * containing the name of a temporary file. It processes the delimiter and
 * updates the tokens linked list as follows:
 * - The type of the delimiter token is set to REDIRECT_IN
 * - The token value is set to an empty string
 * - A new token is created with the type set to WORD and the value set to the
 *   temporary file name
 * - The new token is inserted between the delimiter token and the next token
 *   in the linked list
 * - The delimiter token is freed
 *
 * @param current A pointer to the delimiter token
 * @param delim A pointer to the delimiter token
 * @param tempfile A string containing the name of a temporary file
 */
void	ft_process_delimiter(t_token *current, t_token *delim, char *tempfile)
{
	t_token	*filename_token;

	current->type = REDIRECT_IN;
	ft_free(current->val.value);
	current->val.value = ft_safe_strdup("");
	ft_free(current->val.og_value);
	current->val.og_value = ft_safe_strdup("");
	filename_token = ft_safe_calloc(sizeof(t_token));
	if (!filename_token)
		return ;
	filename_token->type = WORD;
	filename_token->val.value = ft_safe_strdup(tempfile);
	filename_token->val.og_value = ft_safe_strdup(tempfile);
	filename_token->quoted = 0;
	filename_token->prev = current;
	filename_token->next = delim->next;
	current->next = filename_token;
	if (delim->next)
		delim->next->prev = filename_token;
	ft_free_token(delim);
}
