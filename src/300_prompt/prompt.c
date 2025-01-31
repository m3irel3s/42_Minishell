/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/31 14:29:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Constructs and returns a shell prompt string.
 *
 * This function retrieves the current working directory and the
 * username from the environment. It constructs a prompt string
 * in the format "user@cwd $ " using the retrieved information.
 * If the working directory or username cannot be retrieved, it
 * defaults to "unknown" and "user" respectively.
 *
 * @return A pointer to the dynamically allocated prompt string.
 *         The caller is responsible for freeing the memory.
 */

char	*ft_set_prompt(void)
{
	char	*cwd;
	char	*user;
	char	*prompt;
	size_t	len;
    int i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("unknown");
	user = getenv("USER");
	if (!user)
		user = "user";
	len = ft_strlen(user) + ft_strlen(cwd) + 4 + 1; // 4 for "@ $ ", 1 for '\0'
	prompt = ft_safe_malloc(len);
	i = 0;
	while (*user)
		prompt[i++] = *user++;
	prompt[i++] = '@';
	while (*cwd)
		prompt[i++] = *cwd++;
	prompt[i++] = ' ';
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	free(cwd);
	return (prompt);
}
