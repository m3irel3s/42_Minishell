/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 11:56:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_input_element(t_shell *shell, size_t *i,
					int *is_export);
static t_status	ft_handle_non_operator(t_shell *shell, size_t *i,
					int *is_export);

/**
 * @brief Tokenizes the input string of the shell.
 *
 * This function iterates through each character of the shell's input string,
 * identifying and processing tokens. It skips over spaces and handles both
 * operators and non-operators by calling respective handler functions.
 * If the input or shell is invalid, it sets an error status. If any error
 * occurs during tokenization, it returns ERROR and sets the shell's exit
 * status to failure.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @return SUCCESS if tokenization is successful; otherwise, returns ERROR.
 */

t_status	ft_tokenize(t_shell *shell)
{
	size_t	i;
	int		is_export;

	if (!shell || !shell->input)
	{
		shell->exit_status = EXIT_FAILURE;
		ft_printf(STDERR_FILENO, ERR_TOKENIZATION_FAIL);
		return (ERROR);
	}
	i = 0;
	is_export = 0;
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
			i++;
		else if (ft_process_input_element(shell, &i, &is_export) != SUCCESS)
		{
			shell->exit_status = EXIT_FAILURE;
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Processes a single element of the input string of the shell.
 *
 * This function identifies the type of the current character in the input
 * string and calls the respective handler function. If the character is an
 * operator, it calls ft_handle_operator. If the character is a non-operator,
 * it calls ft_handle_non_operator. If any error occurs during processing,
 * it sets an error status and returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the input string.
 * @param i A pointer to the index of the current character in the input string.
 * @param is_export A pointer to the flag indicating if the current context is
 * an export.
 *
 * @return Returns ERROR if any error occurs during processing; otherwise,
 * returns SUCCESS.
 */
static t_status	ft_process_input_element(t_shell *shell, size_t *i,
		int *is_export)
{
	if (ft_is_operator(shell->input[*i]))
	{
		if (ft_handle_operator(shell, i, is_export) != SUCCESS)
		{
			ft_printf(STDERR_FILENO, ERR_OPERATOR_HANDLING_FAIL);
			return (ERROR);
		}
	}
	else
	{
		if (ft_handle_non_operator(shell, i, is_export) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Handles a non-operator character in the input.
 *
 * If the character is 'export', it creates an export token and sets the
 * is_export flag. If the flag is set, it handles an export argument.
 * Otherwise, it handles a word.
 *
 * @param shell The shell struct containing the input string.
 * @param i Pointer to the current index in the input string.
 * @param is_export Pointer to the flag indicating if the current context is
 * an export.
 * @return SUCCESS if the token is created and added successfully, ERROR
 * otherwise.
 */
static t_status	ft_handle_non_operator(t_shell *shell, size_t *i,
		int *is_export)
{
	if (ft_is_export_command(shell, *i))
	{
		if (ft_create_export_token(shell, i, is_export) != SUCCESS)
		{
			ft_printf(STDERR_FILENO, ERR_EXPORT_TOKEN_FAIL);
			return (ERROR);
		}
	}
	else if (*is_export)
	{
		if (ft_handle_export_arg(shell, i) != SUCCESS)
		{
			ft_printf(STDERR_FILENO, ERR_EXPORT_ARG_HANDLING_FAIL);
			return (ERROR);
		}
	}
	else
	{
		if (ft_handle_word(shell, i) != SUCCESS)
		{
			ft_printf(STDERR_FILENO, ERR_WORD_HANDLING_FAIL);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
