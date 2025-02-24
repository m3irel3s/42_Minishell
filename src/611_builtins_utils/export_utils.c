/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:15:52 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/24 11:05:17 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_var_chars(char *str)
{
	int	i;

	i = 0;
	if (!str || !(str[i] == '_' || ft_isalpha(str[i])))
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
