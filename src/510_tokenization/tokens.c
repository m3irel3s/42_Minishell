/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 09:54:39 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status ft_process_input_element(t_shell *shell, size_t *i, int *is_export);

t_status	ft_tokenize(t_shell *shell)
{
	size_t	i;
	int		is_export;

	if (!shell || !shell->input)
		return (ERROR);
	i = 0;
	is_export = 0;
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
			i++;
		else
		{
			if (ft_process_input_element(shell, &i, &is_export) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}


static t_status ft_process_input_element(t_shell *shell, size_t *i, int *is_export)
{
	if (ft_is_operator(shell->input[*i]))
	{
		if (ft_handle_operator(shell, i, is_export) != SUCCESS)
			return (ERROR);
	}
	else if (ft_is_export_command(shell, *i))
	{
		if (ft_create_export_token(shell, i, is_export) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (*is_export)
		{
			if (ft_handle_export_arg(shell, i) != SUCCESS)
				return (ERROR);
		}
		else
		{
			if (ft_handle_word(shell, i) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
