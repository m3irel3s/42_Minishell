/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:12:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/12 22:13:41 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if a variable name is valid.
 *
 * Variable name must start with a letter or underscore, followed by
 * alphanumeric characters or underscores.
 *
 * @param name The variable name to check.
 *
 * @return Returns 1 if valid, 0 otherwise.
 */
int	ft_is_valid_variable_name(char *name)
{
	if (!name || !*name)
		return (0);
	if (!isalpha(*name) && *name != '_')
		return (0);
	name++;
	while (*name)
	{
		if (!isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
