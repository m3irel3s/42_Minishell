/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 14:17:45 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_build_prompt(const char *user, const char *cwd);

/**
 * @brief Constructs and returns a colorful shell prompt string.
 *
 * @param shell Pointer to the shell structure.
 * @return A dynamically allocated string containing the prompt, or NULL on
 * failure.
 */
char	*ft_set_prompt(t_shell *shell)
{
	char	*cwd;
	char	*user;
	char	*prompt;

	cwd = ft_get_current_directory(shell);
	if (!cwd)
		return (NULL);
	user = getenv("USER");
	if (!user)
		user = "user";
	prompt = ft_build_prompt(user, cwd);
	ft_free(cwd);
	if (!prompt)
		shell->exit_status = EXIT_FAILURE;
	return (prompt);
}

/**
 * @brief Retrieves the current working directory.
 *
 * @param shell Pointer to the shell structure.
 * @return A dynamically allocated string containing the current
 * working directory, or NULL on failure.
 */
char	*ft_get_current_directory(t_shell *shell)
{
	char	*cwd;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf(STDERR_FILENO, ERR_GET_CWD_FAIL);
		shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	res = ft_strdup_safe(cwd);
	ft_free(cwd);
	if (!res)
		shell->exit_status = EXIT_FAILURE;
	return (res);
}

/**
 * @brief Builds a colorful shell prompt string using the user's name and
 *        current working directory.
 *
 * This function constructs a prompt string formatted with color codes to
 * enhance readability. The prompt includes the user's name and the current
 * working directory, and it is followed by a dollar sign to indicate the
 * shell prompt. The function ensures memory allocation for the prompt
 * string and returns a pointer to it.
 *
 * @param user The username to be included in the prompt.
 * @param cwd The current working directory to be included in the prompt.
 * @return A dynamically allocated string containing the formatted prompt,
 *         or NULL if memory allocation fails.
 */
static char	*ft_build_prompt(const char *user, const char *cwd)
{
	char	*prompt;
	size_t	len;
	size_t	offset;

	len = ft_strlen(user) + ft_strlen(cwd)
		+ ft_strlen(GRN2) + ft_strlen(CYN2) + ft_strlen(RESET2)
		+ 9;
	prompt = ft_safe_malloc(len * sizeof(char));
	if (!prompt)
		return (NULL);
	offset = 0;
	offset += ft_strlcpy(prompt + offset, GRN2, len - offset);
	offset += ft_strlcat(prompt + offset, user, len - offset);
	offset += ft_strlcat(prompt + offset, RESET2, len - offset);
	offset += ft_strlcat(prompt + offset, "@", len - offset);
	offset += ft_strlcat(prompt + offset, CYN2, len - offset);
	offset += ft_strlcat(prompt + offset, cwd, len - offset);
	offset += ft_strlcat(prompt + offset, RESET2, len - offset);
	offset += ft_strlcat(prompt + offset, " $ ", len - offset);
	return (prompt);
}
