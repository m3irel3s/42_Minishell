/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_and_pwd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:43:33 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/13 17:38:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Retrieves the current working directory.
 *
 * If the current working directory cannot be retrieved, updates exit status
 * and returns NULL.
 *
 * @param shell Pointer to the shell structure for updating exit status.
 * @return A dynamically allocated string containing the current working
 * directory, or NULL on failure.
 */
char	*ft_get_current_directory(void)
{
	char	*cwd;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_exit_status = EXIT_FAILURE;
		return (NULL);
	}
	res = ft_safe_strdup(cwd);
	ft_free(cwd);
	if (!res)
	{
		ft_printf(STDERR_FILENO, ERR_STRDUP_FAIL);
		g_exit_status = EXIT_FAILURE;
	}
	return (res);
}
