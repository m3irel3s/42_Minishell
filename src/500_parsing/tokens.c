/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 08:29:32 by meferraz         ###   ########.fr       */
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
	int i;
	int word_started;
	int was_escaped;
	enum e_quote_state current_quote;

	count = 0;
	i = 0;
	word_started = 0;
	was_escaped = 0;
	current_quote = NO_QUOTE;
	while (input[i])
	{
		if (current_quote == NO_QUOTE && ft_is_space(input[i]) && !was_escaped)
		{
			if (word_started)
			{
				count++;
				word_started = 0;
			}
			while (ft_is_space(input[i]))
				i++;
			if (input[i])
				word_started = 1;
		}
		else
		{
			word_started = 1;

		}
	}
	return (SUCCESS);
}
