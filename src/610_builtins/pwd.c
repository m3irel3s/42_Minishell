/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:22:08 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/14 17:38:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

/**
 * @brief The pwd built-in command. Prints the absolute path of the current
 * working directory.
 *
 * @details Calls ft_get_current_directory() to get the current working
 * directory. If the call fails, prints an error message and sets
 * g_exit_status to EXIT_FAILURE. Otherwise, prints the path and sets
 * g_exit_status to EXIT_SUCCESS.
 */
void	ft_pwd(void)
{
	char	*path;

	path = ft_get_current_directory();
	if (!path)
	{
		ft_print_error(ERR_GET_CWD_FAIL);
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	ft_printf(STDOUT_FILENO, "%s\n", path);
	ft_free(path);
	g_exit_status = EXIT_SUCCESS;
}
