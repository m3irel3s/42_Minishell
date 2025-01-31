/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/31 14:16:43 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_set_prompt(void)
{
	char	*cwd;
	char	*user;
	char	*prompt;
	size_t	len;

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
