/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 11:29:43 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status ft_handle_unclosed_quote(t_shell *shell, size_t *index, char quote_char);

/**
 * @brief Tokenizes the input string of the shell.
 *
 * Checks for valid input and passes control to ft_process_and_tokenize.
 * If an error occurs, the function returns ERROR. If all operations succeed,
 * the function returns SUCCESS.
 *
 * @param shell A pointer to the shell structure containing the input
 *              to be tokenized.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
 */
int	ft_tokenize(t_shell *shell)
{
	if (!shell || !shell->input)
		return (ERROR);
	return (ft_process_and_tokenize(shell));
}

/**
 * @brief Processes and tokenizes the input entered by the user in the shell.
 *
 * This function processes and tokenizes the input string of the shell.
 * It iterates through the input string and checks for quotes, operators,
 * and words. If a quote is found, it processes the quoted string and
 * creates a token. If an operator is found, it creates a token. If a
 * word is found, it creates a token. If an error occurs during token
 * creation, the function returns ERROR. If all operations succeed,
 * the function returns SUCCESS.
 *
 * @param shell A pointer to the shell structure containing the input
 *              to be tokenized.
 *
 * @return Returns SUCCESS if the input is successfully tokenized;
 *         otherwise, returns ERROR.
 */
static t_status	ft_process_and_tokenize(t_shell *shell)
{
	size_t			i;
	size_t			start;
	t_token_type	type;
	char			quote_char;
	int				quoted_status;

	i = 0;
	quote_char = 0;
	quote_status = 0;
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
		{
			i++;
			continue ;
		}
		else if (ft_is_quote(shell->input[i]) && !quote_char)
		{
			quote_char = shell->input[i];
			if (quote_char == '\'')
				quoted_status = 1;
			else
				quoted_status = 2;
			start = i + 1;
			i++;
			while (shell->input[i] && shell->input[i] != quote_char)
				i++;
			if (!shell->input[i])
			{
				if (ft_handle_unclosed_quote(shell, &i, quote_char) == ERROR)
					return (ERROR);
			}
			if (shell->input[i] == quote_char)
			{
				i++;
				type = ft_determine_token_type(shell->input + start, i - start - 1);
				if (ft_create_and_add_token(shell, start, (i - 1), type, quoted_status) == ERROR)
					return (ERROR);
			quote_char = 0;
			}
		}
		else if (ft_is_operator(shell->input[i]))
		{
			start = i;
			while (ft_is_operator(shell->input[i]))
				i++;
			type = ft_determine_token_type(shell->input + start, i - start);
			if (ft_create_and_add_token(shell, start, i, type, quoted_status) == ERROR)
				return (ERROR);
		}
		else
		{
			start = i;
			while (shell->input[i] && !ft_is_space(shell->input[i]) &&
				!ft_is_operator(shell->input[i]) && !ft_is_quote(shell->input[i]))
				i++;
			type = ft_determine_token_type(shell->input + start, i - start);
			if (ft_create_and_add_token(shell, start, i, type, quoted_status) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Handles unclosed quotes in the input string.
 *
 * If an unclosed quote is found in the input string, this function
 * reads additional input from the user until a matching quote is
 * found. It then appends the additional input to the shell's input
 * string and continues parsing from where it left off. Handles SIGINT
 * during this process to mimic Bash behavior.
 *
 * @param shell A pointer to the shell structure containing the
 *              input string.
 * @param index A pointer to the index in the input string where
 *              the unclosed quote was found.
 *
 * @return Returns SUCCESS if the matching quote is found;
 *         otherwise, returns ERROR.
 */
static t_status	ft_handle_unclosed_quote(t_shell *shell, size_t *index, char quote_char)
{
	struct sigaction	old_sa;
	struct sigaction	sa;
	char				*new_input_line;
	char				*input_buffer;

	sigaction(SIGINT, NULL, &old_sa);
	sa.sa_handler = ft_handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		new_input_line = readline("> ");
		if (!new_input_line)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n", STDERR_FILENO);
			sigaction(SIGINT, &old_sa, NULL);
			return (ERROR);
		}
		input_buffer = ft_strjoin(shell->input, "\n");
		free(shell->input);
		shell->input = ft_strjoin(input_buffer, new_input_line);
		free(input_buffer);
		free(new_input_line);
		*index = ft_strlen(shell->input) - ft_strlen(new_input_line) - 1;
		while (shell->input[*index])
		{
			if (shell->input[*index] == quote_char)
			{
				(*index)++;
				sigaction(SIGINT, &old_sa, NULL);
				return (SUCCESS);
			}
			(*index)++;
		}
	}
}
