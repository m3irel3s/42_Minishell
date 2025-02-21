/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 08:15:47 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if the current position in the input is the start of an export
 * command.
 *
 * @param shell Pointer to the shell structure.
 * @param i Current index in the input string.
 * @return 1 if it's an export command, 0 otherwise.
 */
int	ft_is_export_command(t_shell *shell, size_t i)
{
	if (!shell || !shell->input)
	{
		ft_printf(STDERR_FILENO, ERR_INVALID_SHELL_OR_INPUT);
		shell->exit_status = EXIT_FAILURE;
		return (0);
	}
	return (ft_strncmp(shell->input + i, "export", 6) == 0
		&& (ft_is_space(shell->input[i + 6]) || shell->input[i + 6] == '\0'));
}

/**
 * @brief Creates an export token and adds it to the shell's token list.
 *
 * @param shell Pointer to the shell structure.
 * @param i Pointer to the current index in the input string.
 * @param is_export Pointer to the flag indicating if we're processing an export
 * command.
 * @return SUCCESS if the token was created and added successfully, ERROR
 * otherwise.
 */
t_status	ft_create_export_token(t_shell *shell, size_t *i, int *is_export)
{
	size_t		start;
	t_status	status;

	if (!shell || !shell->input || !i || !is_export)
	{
		ft_printf(STDERR_FILENO, ERR_INVALID_PARAMS);
		shell->exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	start = *i;
	*is_export = 1;
	*i += 6;
	status = ft_create_and_add_token(shell, start, *i, 0);
	if (status == ERROR)
	{
		ft_printf(STDERR_FILENO, ERR_EXPORT_TOKEN_CREATION_FAIL);
		shell->exit_status = EXIT_FAILURE;
	}
	return (status);
}
