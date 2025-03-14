/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:15:52 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/14 17:42:24 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Checks if a string contains valid characters for a variable name.
 *
 * A valid variable name must start with an underscore or an alphabet letter.
 * The rest of the characters must be alphanumeric, an underscore, or a '+'.
 * If a '+' is found, the next character must be '='.
 *
 * @param str The string to check.
 * @return 0 if the string is valid, 1 otherwise.
 */
int	ft_check_var_chars(char *str)
{
	int	i;

	if (!str || !(str[0] == '_' || ft_isalpha(str[0])))
		return (EXIT_FAILURE);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				return (SUCCESS);
			else
				return (EXIT_FAILURE);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (SUCCESS);
}
