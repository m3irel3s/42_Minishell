/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:26:26 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 16:12:38 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_init_new_token(t_shell *shell, size_t start,
				size_t end, int quoted);
static void		ft_add_token_to_shell(t_shell *shell, t_token *new_token);

/**
 * @brief Creates a new token from a specified substring of the shell's input
 *        and adds it to the shell's token list.
 *
 * This function initializes a new token with the input substring between the
 * specified start and end indices. It first checks for valid input, and if
 * the input is invalid or the token creation fails, it updates the shell's
 * exit_status and prints an error message. If the substring length is zero,
 * the function returns SUCCESS without creating a token. Upon successful
 * token creation, the token is added to the shell's token list.
 *
 * @param shell The shell struct containing the token list and environment info.
 * @param start The starting index of the token's value in the shell's input.
 * @param end The ending index of the token's value in the shell's input.
 * @param quoted Indicates whether the token is quoted (1 if quoted, 0 otherwise).
 *
 * @return SUCCESS if the token is created and added successfully, ERROR on failure.
 */
int	ft_create_and_add_token(t_shell *shell, size_t start,
		size_t end, int quoted)
{
	t_token	*new_token;

	if (end - start == 0)
		return (SUCCESS);
	if (!shell || !shell->input)
	{
		shell->exit_status = EXIT_FAILURE;
		ft_printf(STDERR_FILENO, ERR_INVALID_SHELL_OR_INPUT);
		return (ERROR);
	}
	new_token = ft_init_new_token(shell, start, end, quoted);
	if (!new_token)
	{
		shell->exit_status = EXIT_FAILURE;
		ft_printf(STDERR_FILENO, ERR_TOKEN_CREATION_FAIL);
		return (ERROR);
	}
	ft_add_token_to_shell(shell, new_token);
	return (SUCCESS);
}

/**
 * @brief Allocates a new token and initializes its value, type, and
 * quote status.
 *
 * This function allocates a new token and initializes its value with the
 * substring of the shell's input from the given start to end indices. Then,
 * it determines the type of the token by calling ft_determine_token_type.
 * If memory allocation fails, it updates the shell's exit_status and prints
 * an error message.
 *
 * @param shell The shell struct containing the token list and environment info.
 * @param start The index of the start of the substring in the shell's input.
 * @param end The index of the end of the substring in the shell's input.
 * @param quoted Whether the token is quoted or not.
 *
 * @return A pointer to the new token on success, NULL on failure.
 */
static t_token	*ft_init_new_token(t_shell *shell, size_t start,
				size_t end, int quoted)
{
	t_token	*new_token;

	new_token = ft_safe_malloc(sizeof(t_token));
	if (!new_token)
	{
		shell->exit_status = EXIT_FAILURE;
		ft_printf(STDERR_FILENO, ERR_MALLOC_FAIL);
		return (NULL);
	}
	new_token->value = ft_substr(shell->input, start, end - start);
	if (!new_token->value)
	{
		ft_free(new_token);
		shell->exit_status = EXIT_FAILURE;
		ft_printf(STDERR_FILENO, ERR_SUBSTR_FAIL);
		return (NULL);
	}
	new_token->type = ft_determine_token_type(shell, new_token->value,
		end - start);
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->quoted = quoted;
	return (new_token);
}

/**
 * @brief Appends a new token to the end of the shell's token list.
 *
 * If the shell's token list is empty, sets the new token as the first token.
 * Otherwise, iterates through the list until it finds the last token and
 * appends the new token to it.
 *
 * @param shell The shell struct containing the token list to be updated.
 * @param new_token The new token to be appended to the list.
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
