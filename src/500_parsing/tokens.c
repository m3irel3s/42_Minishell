/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 10:54:57 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int	ft_count_tokens(char *input);

int	ft_tokenize(t_shell *shell)
{
	int	tokens;

	tokens = ft_count_tokens(shell->input);
	ft_printf("There are %d tokens. \n", tokens);

	return (SUCCESS);
}

static	int	ft_count_tokens(char *input)
{
	int count;

	count = 0;
	return (count);
}
