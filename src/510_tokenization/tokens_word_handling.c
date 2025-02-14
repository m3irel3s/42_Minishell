/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_word_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:51:19 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/14 13:39:39 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command_type	ft_determine_command_type(char *command);
static int ft_is_export_terminator(const char *word);

t_status ft_handle_word(t_shell *shell, size_t *i, int *q_stat)
{
	t_token *new_token;
	char    *word;
	size_t  start = *i;
	char    quote_char = 0;

	while (shell->input[*i])
	{
		if (ft_is_quote(shell->input[*i]))
		{
			if (!*q_stat)
			{
				quote_char = shell->input[*i];
				*q_stat = 1;
			}
			else if (shell->input[*i] == quote_char)
			{
				*q_stat = 0;
				if (!shell->in_export && *i > start)
				{
					// End of a quoted string, create a token
					word = ft_substr(shell->input, start, *i - start + 1);
					new_token = ft_create_token(word, WORD);
					new_token->quoted = (quote_char == '\'') ? 1 : 2; // 1 for single quotes, 2 for double quotes
					free(word);
					if (!new_token)
						return (ERROR);
					ft_add_token_to_list(shell, new_token);
					(*i)++;
					start = *i;
					continue;
				}
			}
		}
		else if (!*q_stat && (ft_is_space(shell->input[*i]) || ft_is_operator(shell->input[*i])))
		{
			break;
		}
		(*i)++;
	}

	if (*i > start)
	{
		word = ft_substr(shell->input, start, *i - start);
		new_token = ft_create_token(word, WORD);
		new_token->quoted = *q_stat ? ((quote_char == '\'') ? 1 : 2) : 0;
		free(word);
		if (!new_token)
			return (ERROR);
		if (ft_determine_command_type(new_token->value) == EXPORT_CMD)
			shell->in_export = 1;
		if (shell->in_export && ft_is_export_terminator(new_token->value))
			shell->in_export = 0;
		ft_add_token_to_list(shell, new_token);
	}

	return (SUCCESS);
}


/**
 * @brief Determines the command type of the given command.
 *
 * Checks the command and returns the corresponding command type.
 *
 * @param command The command to be checked.
 *
 * @return Returns the corresponding command type.
 */
t_command_type	ft_determine_command_type(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		return (ECHO_CMD);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (CD_CMD);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (PWD_CMD);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (EXPORT_CMD);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (UNSET_CMD);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (ENV_CMD);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (EXIT_CMD);
	else
		return (NONE);
}

static int	ft_is_export_terminator(const char *word)
{
	const char	*terminators[] = {
		"|", "'|'", "\"|\"",
		">", "'>'", "\">\"",
		">>", "'>>'", "\">>\"",
		"<", "'<'", "\"<\"",
		"<<", "'<<'", "\"<<\"",
		NULL
	};
	int			i;

	i = 0;
	while (terminators[i])
	{
		if (ft_strcmp(word, terminators[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
