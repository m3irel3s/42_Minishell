/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:22:08 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 14:34:46 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*path;

	path = ft_get_current_directory(shell);
	ft_printf(1, "%s\n", path);
	ft_free(path);
}
