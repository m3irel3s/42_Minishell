/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:15:52 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:20 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_var_chars(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (-1);
	if (!(ft_isalpha(var[i]) || var[i] == '_'))
		return (-1);
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (-1);
		i++;
	}
	return (SUCCESS);
}
