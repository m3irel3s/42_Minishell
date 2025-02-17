/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:14:30 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/17 14:25:22 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_exit_status(t_shell *shell, size_t *i);
static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
				size_t start);
static char *ft_expand_variable(t_shell *shell, char *token, size_t *i,
				size_t start);

char	*ft_handle_dollar(t_shell *shell, char *token, size_t *i)
{
	char	*res;
	size_t	start;

	res = NULL;
	(*i)++;
	if (token[*i] == '?')
		res = ft_expand_exit_status(shell, i);
	else
	{
		start = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			(*i)++;
		res = ft_expand_variable(shell, token, i, start);
	}
	return (res);
}

static char	*ft_expand_exit_status(t_shell *shell, size_t *i)
{
	char	*res;

	(*i)++;
	res = ft_itoa(shell->exit_status);
	return (res);
}

static char	*ft_expand_variable(t_shell *shell, char *token, size_t *i,
	size_t start)
{
	char	*var_name;
	char	*var_value;
	char	*res;

	var_name = ft_substr(token, start, *i - start);
	if (!var_name)
		return (ft_strdup("$"));
	var_value = ft_get_var_value(var_name, shell->dup_env);
	free(var_name);
	if (var_value)
		res = ft_strdup_safe(var_value);
	else
		res = ft_strdup("");
	return (res);
}
