/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:16:04 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/01 17:25:57 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_check_redirect_operator(char *input, int i);

t_status	ft_validate_redirects(char *input)
{
	int	i;
	int	new_index;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (ft_skip_quotes(input, &i, input[i]) == ERROR)
				return (ERROR);
			continue ;
		}
		if (input[i] == '<' || input[i] == '>')
		{
			new_index = ft_check_redirect_operator(input, i);
			if (new_index == -1)
				return (ERROR);
			i = new_index;
		}
		else
			i++;
	}
	return (SUCCESS);
}

static int	ft_check_redirect_operator(char *input, int i)
{
	int	operator_len;

	operator_len = 1;
	if (input[i + 1] == input[i])
		operator_len = 2;
	i += operator_len;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (!input[i] || ft_strchr("<>|", input[i]))
	{
		if (!input[i])
			ft_print_syntax_error("newline");
		else
			ft_print_syntax_error(&input[i]);
		return (-1);
	}
	return (i);
}
