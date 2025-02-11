/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:55:08 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 15:32:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_variables(char *input, char **envp);

/**
 * @brief Expands variables in the shell's token list.
 *
 * This function iterates through the shell's token list and checks
 * if each token is a word and is not quoted. If both conditions are
 * true, it expands variables in the token by calling
 * ft_expand_variables and updates the token's value. It then moves
 * on to the next token in the list.
 *
 * @param shell A pointer to the shell structure containing the token
 *              list and the environment variables to be used for
 *              expansion.
 */
void	ft_expand_tokens(t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	current = shell->tokens;
	while (current)
	{
		if (current->type == WORD && current->quoted != 1)
		{
			expanded = expand_variables(current->value, shell->envp);
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
}

static char	*ft_expand_variables(char *input, char **envp)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	c[2];
	size_t	i;
	size_t	start;

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			i++;
			start = i;
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
				i++;
			var_name = ft_substr(input, start, i - start);
			var_value = ft_get_env_value(var_name, envp);
			free(var_name);
			if (var_value)
			{
				temp = ft_strjoin(result, var_value);
				free(result);
				result = temp;
			}
		}
		else
		{
			c[0] = input[i++];
			c[1] = '\0';
			temp = ft_strjoin(result, c);
			free(result);
			result = temp;
		}
	}
	return (result);
}
