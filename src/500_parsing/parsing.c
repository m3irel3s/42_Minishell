/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:29:46 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/03 10:53:40 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_input(t_shell *shell)
{
	if (ft_tokenize(shell) != SUCCESS)
		return (ERROR);
	/*if (ft_validate_syntax(shell) != SUCCESS)
	{
		perror("Error syntax!");
		return (ERROR);
	}*/
	return (SUCCESS);
}
