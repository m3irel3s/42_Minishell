/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:22:08 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 22:46:37 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	ft_pwd(void)
{
	char	*path;

	path = ft_get_current_directory();
	if (!path)
	{
		ft_print_error(ERR_GET_CWD_FAIL);
		g.g_exit_status = EXIT_FAILURE;
		return ;
	}
	ft_printf(STDOUT_FILENO, "%s\n", path);
	ft_free(path);
	g.g_exit_status = EXIT_SUCCESS;
}
