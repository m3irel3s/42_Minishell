/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 12:34:41 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_token(t_shell *shell, char *token, int quoted);
static char	*ft_handle_dollar(t_shell *shell, char *token, size_t *i,char **envp);

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
	char	*new_expanded;
	char	*temp;
	char	c[2];
	size_t	i;

	expanded_value = ft_strdup("");
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && quoted != 1)
		{
			temp = ft_handle_dollar(shell, token, &i, shell->dup_env);
			if (temp)
			{
				new_expanded = ft_strjoin(expanded_value, temp);
				free(expanded_value);
				expanded_value = new_expanded;
				free(temp);
			}
		}
		else
		{
			c[0] = token[i];
			c[1] = '\0';
			new_expanded = ft_strjoin(expanded_value, c);
			free(expanded_value);
			expanded_value = new_expanded;
			i++;
		}
	}
	return (expanded_value);
}

static char *ft_handle_dollar(t_shell *shell, char *token, size_t *i, char **envp)
{
	char *var_name;
	char *var_value;
	size_t start;
	char *res;

	res = NULL;
	(*i)++;
	if (token[*i] == '?')
	{
		(*i)++;
		res = ft_itoa(shell->exit_status);
	}
	else
	{
		start = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			(*i)++;
		var_name = ft_substr(token, start, *i - start);
		if (!var_name)
			return (ft_strdup("$"));
		var_value = ft_get_var_value(var_name, envp);
		free(var_name);
		if (var_value)
			res = ft_strdup_safe(var_value);
		else
			res = ft_strdup("");
	}
	return (res);
}
