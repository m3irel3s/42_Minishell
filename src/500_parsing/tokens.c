/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/03 10:51:34 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int	ft_count_tokens(char *input);
static	int	ft_is_operator(char c);
static	int	ft_is_space(char c);

int	ft_tokenize(t_shell *shell)
{
	void(shell);
	return (SUCCESS);
}

static	int	ft_count_tokens(char *input)
{
	return (SUCCESS);
}

static	int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '<<' || c == '>>');
}

static	int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 8 && c <= 13));
}
