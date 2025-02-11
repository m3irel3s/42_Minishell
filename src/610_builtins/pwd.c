/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:22:08 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 15:00:14 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*path;
	(void)shell;
	path = ft_get_current_directory();
	ft_printf(1, "%s\n", path);
}
