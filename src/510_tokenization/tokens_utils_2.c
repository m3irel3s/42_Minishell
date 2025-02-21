/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:26:26 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 14:35:50 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_init_new_token(t_shell *shell, size_t start,
					size_t end, int quoted);
static void		ft_add_token_to_shell(t_shell *shell, t_token *new_token);

/**
 * @brief Creates a new token from a substring of the shell's input and adds
 *        it to the shell's token list.
 *
 * This function initializes a new token using a substring of the shell's input
 * from the specified start to end positions. If the substring is non-empty,
 * it creates the token and appends it to the shell's token list. The function
 * returns SUCCESS if the token is successfully created and added, or an
 * appropriate error if the input is invalid or token creation fails.
 *
 * @param shell Pointer to the shell structure containing the input and token list.
 * @param start The start index of the token's value in the input string.
 * @param end The end index of the token's value in the input string.
 * @param quoted Indicates whether the token is quoted (1 for quoted, 0 otherwise).
 *
 * @return SUCCESS if the token is successfully created and added, or an error
 *         code if the input is invalid or token creation fails.
 */

int	ft_create_and_add_token(t_shell *shell, size_t start,
		size_t end, int quoted)
{
	t_token	*new_token;

	if (end - start == 0)
		return (SUCCESS);
	if (!shell || !shell->input)
		return (ft_print_error(shell, ERR_INVALID_SHELL_OR_INPUT));
	new_token = ft_init_new_token(shell, start, end, quoted);
	if (!new_token)
		return (ft_print_error(shell, ERR_TOKEN_CREATION_FAIL));
	ft_add_token_to_shell(shell, new_token);
	return (SUCCESS);
}

/**
 * @brief Initializes a new token with specified input and attributes.
 *
 * Allocates memory for a new token structure and sets its value using a
 * substring of the shell input from the given start to end positions. If
 * memory allocation or substring extraction fails, the function returns
 * NULL and prints an appropriate error message. The token type is determined
 * based on its value, and the token's quoted state is set based on the input
 * parameter. The newly created token is returned.
 *
 * @param shell Pointer to the shell structure containing input data.
 * @param start The start index of the token's value in the input string.
 * @param end The end index of the token's value in the input string.
 * @param quoted Indicates whether the token is quoted (1 for quoted, 0 otherwise).
 *
 * @return A pointer to the newly created token, or NULL on failure.
 */

static t_token	*ft_init_new_token(t_shell *shell, size_t start,
				size_t end, int quoted)
{
	t_token	*new_token;

	new_token = ft_safe_malloc(sizeof(t_token));
	if (!new_token)
		return (ft_print_error(shell, ERR_MALLOC_FAIL), NULL);
	new_token->value = ft_substr(shell->input, start, end - start);
	if (!new_token->value)
	{
		ft_free(new_token);
		ft_print_error(shell, ERR_SUBSTR_FAIL);
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
 * If the shell's token list is empty, the new token becomes the first token in
 * the list. Otherwise, the function iterates through the list to find the last
 * token and appends the new token to it. The new token's 'next' field is set to
 * NULL and its 'prev' field is set to the last token in the list.
 *
 * @param shell The shell structure containing the token list.
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
