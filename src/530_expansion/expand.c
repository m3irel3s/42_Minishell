/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 14:44:39 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_token(t_shell *shell, char *token, int quoted);
static char	*ft_process_char(char *expanded_value, char c);

t_status	ft_expand(t_shell *shell)
{
	t_token *current;
	char *expanded_value;

	current = shell->tokens;
	while (current)
	{
		expanded_value = ft_expand_token(shell, current->value, current->quoted);
		if (!expanded_value)
			return (ERROR);
		free(current->value);
		current->value = expanded_value;
		current = current->next;
	}
	return (SUCCESS);
}

static char	*ft_expand_token(t_shell *shell, char *token, int quoted)
{
	char	*expanded_value;
	char	*temp;
	size_t	i;

	expanded_value = ft_strdup("");
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && quoted != 1)
		{
			temp = ft_handle_dollar(shell, token, &i);
			if (temp)
			{
				expanded_value = ft_strjoin_gnl(expanded_value, temp);
				free(temp);
			}
		}
		else
		{
			expanded_value = ft_process_char(expanded_value, token[i]);
			i++;
		}
	}
	return (expanded_value);
}

static char	*ft_process_char(char *expanded_value, char c)
{
	char	c_str[2];
	char	*new_expanded;

	c_str[0] = c;
	c_str[1] = '\0';
	new_expanded = ft_strjoin(expanded_value, c_str);
	free(expanded_value);
	return (new_expanded);
}
