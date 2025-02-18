/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 08:14:56 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_export_command(t_shell *shell, size_t i)
{
	return (ft_strncmp(shell->input + i, "export", 6) == 0
		&& (ft_is_space(shell->input[i + 6]) || shell->input[i + 6] == '\0'));
}

t_status	ft_create_export_token(t_shell *shell, size_t *i, int *is_export)
{
	size_t	start;

	start = *i;
	*is_export = 1;
	*i += 6;
	return (ft_create_and_add_token(shell, start, *i, 0));
}

t_status	ft_print_unmatched_quote_error(void)
{
	ft_putstr_fd(ERR_UNMATCHED_QUOTE, 2);
	return (ERROR);
}
