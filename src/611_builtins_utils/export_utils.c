/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:15:52 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 17:49:07 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_var_chars(char *str)
{
	int	i;

	if (!str || !(*str == '_' || ft_isalpha(*str)))
		return (EXIT_FAILURE);
	i = 1;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (SUCCESS);
}