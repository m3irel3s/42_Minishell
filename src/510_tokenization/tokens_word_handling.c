/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_word_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:51:19 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/12 21:55:20 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_command_type	ft_determine_command_type(char *command);
static t_status	ft_extract_word(t_shell *s, size_t *i, char **w);

/**
 * @brief Processes a word token in the shell input.
 *
 * Extracts the word, checks if it is an export command, creates a token for
 * the word, and adds it to the shell's token list.
 *
 * @param shell A pointer to the shell structure.
 * @param i A pointer to the current index in the shell's input string.
 *
 * @return Returns SUCCESS if the word is processed and tokenized correctly,
 *         ERROR otherwise.
 */
t_status	ft_handle_word(t_shell *shell, size_t *i)
{
	char		*word;
	t_token		*new_token;
	t_status	status;

	status = ft_extract_word(shell, i, &word);
	if (status != SUCCESS)
		return (status);
	if (ft_determine_command_type(word) == EXPORT_CMD)
		shell->in_export = 1;
	new_token = ft_create_token(word, WORD);
	free(word);
	if (!new_token)
		return (ERROR);
	ft_add_token_to_list(shell, new_token);
	return (SUCCESS);
}

/**
 * @brief Extracts a word from the shell's input string.
 *
 * This function extracts the word starting from the current index in the
 * shell's input string, and updates the index to the end of the extracted word.
 * The function skips any spaces, operators, and quotes in the input string.
 *
 * @param s A pointer to the shell structure.
 * @param i A pointer to the current index in the shell's input string.
 * @param w A pointer to a character pointer where the extracted word will be
 *          stored.
 *
 * @return Returns SUCCESS if the word is successfully extracted and stored,
 *         ERROR otherwise.
 */
static t_status	ft_extract_word(t_shell *s, size_t *i, char **w)
{
	size_t	start;

	start = *i;
	while (s->input[*i] && !ft_is_space(s->input[*i])
		&& !ft_is_operator(s->input[*i]) && !ft_is_quote(s->input[*i]))
		(*i)++;
	*w = ft_substr(s->input, start, *i - start);
	if (!*w)
		return (ERROR);
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
static t_command_type	ft_determine_command_type(char *command)
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
