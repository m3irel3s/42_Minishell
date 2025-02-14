/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:01 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 16:50:37 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// check if the var exists
// 

void	ft_unset(t_shell *shell)
{
	t_token	*curr;
	
	curr = shell->tokens;
	if (!curr->next)
		return ;
	while (curr->next)
	{
		
	}
	
}