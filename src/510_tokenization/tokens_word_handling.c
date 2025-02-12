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
static t_status	ft_process_export_assignment(t_shell *shell, char *word);
static t_command_type	ft_determine_command_type(char *command);
static t_status	ft_handle_word_process(t_shell *shell, size_t *i,
					size_t start, char **word);

/**
 * @brief Processes a word and adds it as a token.
 *
 * Handles regular words and the special case of 'export' command arguments.
 *
 * @param shell A pointer to the shell structure.
 * @param i A pointer to the current index in the input string.
 * @param quoted_status The quoted status.
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_handle_word(t_shell *shell, size_t *i, int quoted_status)
{
	size_t			start;
	char			*word;
	t_status		status;

	start = *i;
	status = ft_handle_word_process(shell, i, start, &word);
	if (status != SUCCESS)
		return (status);
	if (shell->in_export)
	{
		status = ft_process_export_assignment(shell, word);
		shell->in_export = 0;
	}
	else
	{
		t_token	*new_token = ft_create_token(word, WORD);

		if (!new_token)
			status = ERROR;
		else
			ft_add_token_to_list(shell, new_token);
	}
	free(word);
	return (status);
}

/**
 * @brief Processes a word and returns its value.
 *
 * @param shell A pointer to the shell structure.
 * @param i A pointer to the current index in the input string.
 * @param start The start index of the word
 * @param word A pointer to the word
 *
 * @return Returns SUCCESS if successful, ERROR otherwise.
 */
static t_status	ft_handle_word_process(t_shell *shell, size_t *i,
					size_t start, char **word)
{
	size_t			temp_i;
	t_command_type	command_type;

	temp_i = *i;
	while (shell->input[temp_i] && !ft_is_space(shell->input[temp_i])
		&& !ft_is_operator(shell->input[temp_i])
		&& !ft_is_quote(shell->input[temp_i]))
		temp_i++;
	*word = ft_substr(shell->input, start, temp_i - start);
	if (!*word)
		return (ERROR);
	command_type = ft_determine_command_type(*word);
	if (command_type == EXPORT_CMD)
		shell->in_export = 1;
	free(*word);
	while (shell->input[*i] && !ft_is_space(shell->input[*i])
		&& !ft_is_operator(shell->input[*i])
		&& !ft_is_quote(shell->input[*i]))
		(*i)++;
	*word = ft_substr(shell->input, start, *i - start);
	if (!*word)
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
