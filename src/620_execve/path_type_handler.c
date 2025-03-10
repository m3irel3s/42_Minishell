/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_type_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:29:01 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/10 15:55:44 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_path_type ft_check_path_type_err(char *cmd)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			return PATH_EXECUTABLE;
		}
		else if (access(cmd, F_OK) == 0)
		{
			return PATH_NOT_EXECUTABLE;
		}
		return PATH_NOT_FOUND;
	}
	return PATH_NOT_FOUND;
}