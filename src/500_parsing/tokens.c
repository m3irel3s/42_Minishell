/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/03 15:02:11 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static	int	ft_count_tokens(char *input);
static	int	ft_is_operator(char c);
static	int	ft_is_space(char c);
*/
int	ft_tokenize(t_shell *shell)
{
	(void)shell;
	return (SUCCESS);
}

static	int	ft_count_tokens(char *input)
{
	int	count;
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	count = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (input[i])
	{
		if (!in_single_quote && !in_double_quote && ft_is_space(input[i]))
		{
			while (ft_is_space(input[i]))
				i++;
			if (input[i])
				count++;
		}
		else if ()

	}
	(void)input;
	return (SUCCESS);
}
