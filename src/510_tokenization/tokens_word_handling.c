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
static t_status	ft_handle_word_process(t_shell *shell,
	size_t *i, size_t start, char **word, int *quoted_status);


/**
 * @brief Handles a word in the shell input and adds it to the token list.
 *
 * This function processes a word in the shell's input string and creates a new
 * token representing the word. It determines if the word was inside quotes and
 * sets the quoted status of the token accordingly. If the shell is in export
 * mode, the function processes the word as an export assignment and sets the
 * shell's in_export flag to 0. Otherwise, the function adds the new token to the
 * shell's token list. The function returns SUCCESS if successful, otherwise it
 * returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will be
 *          updated to the index after the processed word.
 *
 * @return Returns SUCCESS if the word token is successfully created and added;
 *         otherwise, returns ERROR.
 */
t_status	ft_handle_word(t_shell *shell, size_t *i, int *quoted_status)
{
	size_t		start;
	char		*word;
	t_status	status;
	t_token		*new_token;
	char		*trimmed;

	start = *i;
	status = ft_handle_word_process(shell, i, start, &word, quoted_status);
	if (status != SUCCESS)
		return (status);
	new_token = ft_create_token(word, WORD);
	if (*quoted_status)
	{
		new_token->quoted = *quoted_status;
		trimmed = ft_strtrim(word, "'\"");
		free(new_token->value);
		new_token->value = trimmed;
	}
	else
		new_token->quoted = 0;
	if (shell->in_export)
	{
		status = ft_process_export_assignment(shell, word);
		shell->in_export = 0;
	}
	else
		ft_add_token_to_list(shell, new_token);
	free(word);
	return (status);
}


/**
 * @brief Processes a word in the shell input and handles quotes.
 *
 * This function takes a pointer to the current index in the shell's input
 * string and advances it until a space or a special character is encountered.
 * It also handles quoted strings by tracking whether the word is inside single
 * or double quotes. Finally, it determines if the word is an export command and
 * sets the shell's in_export flag accordingly.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the current index in the input string, which will be
 *          updated to the index after the processed word.
 * @param start The starting index for the word in the input string.
 * @param word A pointer to a pointer that will hold the processed word.
 *
 * @return Returns SUCCESS if the word is successfully processed;
 *         otherwise, returns ERROR.
 */
static t_status	ft_handle_word_process(t_shell *shell,
	size_t *i, size_t start, char **word, int *quoted_status)
{
	size_t			temp_i;
	t_command_type	command_type;
	char			quote_char;
	int				quote_stack[10];
	int				quote_depth;

	temp_i = *i;
	quote_char = 0;
	quote_depth = 0;
	ft_memset(quote_stack, 0, sizeof(quote_stack));
	while (shell->input[temp_i])
	{
		if (shell->input[temp_i] == '\\' && shell->input[temp_i + 1])
		{
			temp_i += 2;
			continue;
		}
		if (ft_is_quote(shell->input[temp_i])
			&& (temp_i == start || shell->input[temp_i - 1] != '\\'))
		{
			if (!*quoted_status)
			{
				quote_char = shell->input[temp_i];
				if (quote_char == '\'')
					*quoted_status = 1;
				else
					*quoted_status = 2;
				quote_stack[quote_depth++] = quote_char;
			}
			else if (shell->input[temp_i] == quote_stack[quote_depth - 1])
			{
				quote_depth--;
				if (quote_depth == 0)
				{
					*quoted_status = 0;
					quote_char = 0;
				}
			}
			else
			{
				quote_stack[quote_depth++] = shell->input[temp_i];
				if (quote_stack[quote_depth - 1] == '\'')
					*quoted_status = 1;
				else
					*quoted_status = 2;
			}
			temp_i++;
			continue;
		}
		if (!*quoted_status && ft_is_space(shell->input[temp_i]))
			break;
		temp_i++;
	}
	if (quote_depth > 0)
	{
		ft_putstr_fd("minishell: error: unmatched quote\n", STDERR_FILENO);
		return (ERROR);
	}
	*word = ft_substr(shell->input, start, temp_i - start);
	if (!*word)
		return (ERROR);
	command_type = ft_determine_command_type(*word);
	if (command_type == EXPORT_CMD)
		shell->in_export = 1;
	*i = temp_i;
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
