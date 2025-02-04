/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/04 08:45:04 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int	ft_count_tokens(char *input);

int	ft_tokenize(t_shell *shell)
{
	int tokens;

	tokens = ft_count_tokens(shell->input);
	ft_printf("There are %d tokens. \n", tokens);
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
			ft_update_quote_state(input[i], &current_quote, &was_escaped);
			if (current_quote == NO_QUOTE && ft_is_operator(input[i]) && !was_escaped)
			{
				if (word_started)
				{
					count++;
					word_started = 0;
				}
				count++;
				if (input[i + 1] && ft_is_operator(input[i + 1]))
					i++;
				else if (input[i] == '\\' && !was_escaped)
				{
					was_escaped = 1;
					if (input[i + 1] == '\n')
						i += 2;
					else
						i++;
					continue;
				}
				was_escaped = 0;
			}
		}
		i++;
	}
	if (word_started)
		count++;
	return (count);
}
