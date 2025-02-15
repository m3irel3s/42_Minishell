/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/15 09:22:10 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status ft_handle_operator(t_shell *shell, size_t *i, int *is_export);

int ft_tokenize(t_shell *shell)
{
	size_t i;
	int is_export;

	i = 0;
	is_export = 0;
	if (!shell || !shell->input)
		return (ERROR);
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
			i++;
		else if (ft_is_operator(shell->input[i]))
		{
			if (ft_handle_operator(shell, &i, &is_export) != SUCCESS)
				return (ERROR);
		}
		else
		{
			if (ft_handle_word_token(shell, &i, &is_export) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

static t_status ft_handle_operator(t_shell *shell, size_t *i, int *is_export)
{
	size_t start;

	start = *i;
	if (*is_export)
		*is_export = 0;
	if (ft_is_double_operator(shell->input + *i))
		*i += 2;
	else
		(*i)++;
	return (ft_create_and_add_token(shell, start, *i, 0));
}
