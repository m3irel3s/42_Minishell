/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 10:03:29 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		ft_remove_spaces(char *str);
static t_status	ft_check_quotes(char *input);
static t_status	ft_skip_quotes(char *input, int *i, char quote);
static t_status ft_validate_pipes(char *input);
static t_status	ft_validate_redirects(char *input);

static void	ft_remove_spaces(char *str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	j = 0;
	if (i > 0)
	{
		while (str[j + i])
		{
			str[j] = str[j + i];
			j++;
		}
		str[j] = '\0';
	}
	i = ft_strlen(str);
	while (i > 0 && ft_is_space(str[i - 1]) == 1)
		i--;
	str[i] = '\0';
}

static t_status	ft_check_quotes(char *input)
{
	size_t	i;
	char	quote_char;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote_char = input[i];
			i++;
			while (input[i] && input[i] != quote_char)
				i++;
			if (input[i] != quote_char)
				return (ERROR);
			i++;
		}
		else
			i++;
	}
	return (SUCCESS);
}

static t_status	ft_skip_quotes(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (ft_print_unmatched_quote_error());
	(*i)++;
	return (SUCCESS);
}

static t_status ft_validate_pipes(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
		return (ERROR);
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (ft_skip_quotes(input, &i, input[i]) == ERROR)
				return (ERROR);
			continue ;
		}
		if (input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '\0'))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static t_status	ft_validate_redirects(char *input)
{
	int	i;
	int	operator_len;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (ft_skip_quotes(input, &i, input[i]) == ERROR)
				return (ERROR);
			continue ;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
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
				return (ERROR);
			}
		}
		else
			i++;
	}
	return (SUCCESS);
}

t_status	ft_validate_syntax(char *input)
{
	char	*input_cpy;

	input_cpy = ft_strdup(input);
	if (!input_cpy)
		return (ft_print_error(ERR_MALLOC_FAIL));
	ft_remove_spaces(input_cpy);
	if (ft_strlen(input_cpy) == 0)
		return (ft_free(input_cpy), ERROR);
	if (ft_check_quotes(input_cpy) != SUCCESS)
		return (ft_free(input_cpy), ft_print_unmatched_quote_error());
	if (ft_validate_pipes(input_cpy) != SUCCESS)
		return (ft_free(input_cpy), ft_print_syntax_error("|"));
	if (ft_validate_redirects(input_cpy) != SUCCESS)
		return (ft_free(input_cpy), ERROR);
	ft_free(input_cpy);
	return (SUCCESS);
}
