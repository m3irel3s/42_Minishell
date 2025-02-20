/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 14:26:29 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_build_prompt(const char *user, const char *cwd);

/**
 * @brief Constructs and returns a colorful shell prompt string.
 *
 * Retrieves the username and current working directory to build a prompt
 * in the format "user@cwd $ " with colors. Defaults to "user" and "unknown"
 * if retrieval fails.
 *
 * @return A dynamically allocated string containing the prompt, or NULL on
 * failure.
 */
char	*ft_set_prompt(void)
{
	char	*cwd;
	char	*user;
	char	*prompt;

	cwd = ft_get_current_directory();
	if (!cwd)
		return (NULL);
	user = getenv("USER");
	if (!user)
		user = "user";
	prompt = ft_build_prompt(user, cwd);
	ft_free(cwd);
	return (prompt);
}

/**
 * @brief Retrieves the current working directory.
 *
 * If the current working directory cannot be retrieved, returns NULL.
 *
 * @return A dynamically allocated string containing the current
 * working directory, or NULL on failure.
 */
char	*ft_get_current_directory(void)
{
	char	*cwd;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_printf(STDERR_FILENO, ERR_GET_CWD_FAIL), NULL);
	res = ft_strdup_safe(cwd);
	ft_free(cwd);
	return (res);
}

/**
 * @brief Constructs a colorful shell prompt string.
 *
 * Retrieves the username and current working directory to build a prompt
 * in the format "user@cwd $ " with colors. Defaults to "user" and "unknown"
 * if retrieval fails.
 *
 * @param user The username to use. If NULL, defaults to "user".
 * @param cwd The current working directory to use. If NULL, defaults to
 * "unknown".
 *
 * @return A dynamically allocated string containing the prompt, or NULL
 * on failure.
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
