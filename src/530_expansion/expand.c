/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:55:08 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 16:10:39 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_variables(char *input, char **envp);
static char	*ft_expand_variable(char *input, size_t *i, char **envp);
static char	*ft_append_char(char *result, char c);

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
	t_token *current;
	t_token *next_token;
	char *expanded;

	current = shell->tokens;
	while (current)
	{
		if (current->type == WORD && current->quoted != 1)
		{
			next_token = current->next;
			if (!next_token || next_token->type != EQUAL)
			{
				expanded = ft_expand_variables(current->value, shell->dup_env);
				if (current->quoted == 2)
				{
					char **split_words = ft_split(expanded, ' ');
					if (split_words && split_words[1])
					{
						free(current->value);
						current->value = ft_strdup_safe(split_words[0]);
						for (int j = 1; split_words[j]; j++)
						{
							t_token *new_token = ft_create_token(split_words[j], WORD);
							if (new_token)
							{
								new_token->quoted = 2;
								ft_add_token_to_list(shell, new_token);
							}
						}
						ft_free_split(split_words);
					}
					else
					{
						free(current->value);
						current->value = expanded;
					}
				}
				else
				{
					free(current->value);
					current->value = expanded;
				}
			}
		}
		current = current->next;
	}
}

/**
 * @brief Expands variables in the input string.
 *
 * This function iterates through the input string and checks for variable
 * expansions. If a variable is found, it is replaced with its value from
 * the environment variables provided in envp. The function returns a new
 * string with the expanded variables.
 *
 * @param input The input string to be expanded.
 * @param envp A pointer to an array of environment variables to be used
 *             for expansion.
 * @return Returns a new string with the expanded variables; otherwise,
 *         returns NULL if an error occurs.
 */
static char	*ft_expand_variables(char *input, char **envp)
{
	char	*result;
	char	*temp;
	size_t	i;

	result = ft_strdup_safe("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1])
				|| input[i + 1] == '_'))
			temp = ft_expand_variable(input, &i, envp);
		else
			temp = ft_append_char(result, input[i++]);
		free(result);
		result = temp;
	}
	return (result);
}

/**
 * @brief Expands a single variable from the input string.
 *
 * This function extracts a variable name starting with `$` from the input
 * string and replaces it with its value from `envp`.
 *
 * @param input The input string containing the variable.
 * @param i A pointer to the current index in the input string.
 * @param envp The environment variables array.
 * @return A new string with the expanded variable appended to `result`.
 */
static char	*ft_expand_variable(char *input, size_t *i, char **envp)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	size_t	start;

	(*i)++;
	start = (*i);
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = ft_substr(input, start, (*i) - start);
	var_value = ft_get_env_value(var_name, envp);
	free(var_name);
	if (!var_value)
		return (ft_strdup_safe(""));
	temp = ft_strjoin("", var_value);
	return (temp);
}

/**
 * @brief Appends a single character to a result string.
 *
 * This function appends a single character to an existing result string,
 * reallocating memory as necessary.
 *
 * @param result The current result string.
 * @param c The character to append.
 * @return A new string with the appended character.
 */
static char	*ft_append_char(char *result, char c)
{
	char	str[2];
	char	*temp;

	str[0] = c;
	str[1] = '\0';
	temp = ft_strjoin(result, str);
	return (temp);
}
