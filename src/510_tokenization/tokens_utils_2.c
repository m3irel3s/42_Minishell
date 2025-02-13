/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:26:26 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 12:28:12 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_init_new_token(t_shell *shell, size_t start,
					size_t end, int quoted);
static void		ft_add_token_to_shell(t_shell *shell, t_token *new_token);

/**
 * @brief Creates a new token from a substring of the input and adds it
 * to the shell's token list.
 *
 * This function initializes a new token using a portion of the shell's input
 * string, determined by the start and end indices, and marks it as quoted if
 * specified. The created token is then appended to the shell's token list.
 * If the shell or its input is invalid, or if token creation fails, the function
 * returns ERROR. Otherwise, it returns SUCCESS.
 *
 * @param shell A pointer to the shell structure containing the input string
 *              and token list.
 * @param start The starting index of the substring used to create the token.
 * @param end The ending index of the substring used to create the token.
 * @param quoted An integer indicating whether the token is quoted (1 for single,
 *               2 for double quotes).
 *
 * @return Returns SUCCESS if the token is successfully created and added;
 *         otherwise, returns ERROR.
 */

int	ft_create_and_add_token(t_shell *shell, size_t start,
		size_t end, int quoted)
{
	t_token	*new_token;

	if (!shell || !shell->input)
		return (ERROR);
	new_token = ft_init_new_token(shell, start, end, quoted);
	if (!new_token)
		return (ERROR);
	ft_add_token_to_shell(shell, new_token);
	return (SUCCESS);
}

/**
 * @brief Allocates a new token and initializes its value, type, and
 *        quoted status.
 *
 * This function allocates memory for a new token and copies the given
 * substring of the shell's input into the new token. It then determines
 * the type of the token and sets its quoted status. If memory allocation
 * fails or the token's value cannot be copied, the function returns NULL.
 *
 * @param shell A pointer to the shell structure containing the input
 *              string from which the token value is copied.
 * @param start The starting index of the substring to be copied from
 *              the shell's input string.
 * @param end The ending index of the substring to be copied from the
 *            shell's input string.
 * @param quoted The quoted status of the token to be created.
 *
 * @return Returns a pointer to the newly created token if successful;
 *         otherwise, returns NULL.
 */
static t_token	*ft_init_new_token(t_shell *shell, size_t start,
				size_t end, int quoted)
{
	t_token	*new_token;

	new_token = ft_safe_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(shell->input, start, end - start);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = ft_determine_token_type(new_token->value, end - start);
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->quoted = quoted;
	return (new_token);
}

/**
 * @brief Adds a new token to the end of the shell's token list.
 *
 * If the shell's token list is initially empty, this function sets the
 * new token as the first token in the list. Otherwise, it traverses
 * the existing list and adds the new token to the end of the list,
 * updating the next and previous pointers of the new token and the
 * last token in the list.
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @param new_token A pointer to the new token to be added to the list.
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
