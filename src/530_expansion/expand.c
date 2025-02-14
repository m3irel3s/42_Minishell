/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:55:08 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/14 10:05:57 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expand_variables(char *input, char **envp);
static char	*ft_expand_variable(char *input, size_t *i, char **envp);
static char	*ft_append_char(char *result, char c);
static void ft_handle_word_splitting(t_token *current, char *expanded);

/**
 * @brief Expands variables within tokens in the shell's token list.
 *
 * This function iterates through the shell's list of tokens and expands any
 * variables found within tokens of type WORD that are not quoted. For each
 * such token, the function retrieves the expanded value using the shell's
 * environment. If the token is not quoted, it performs word splitting on the
 * expanded value. Otherwise, it directly updates the token's value with the
 * expanded result. The function modifies the token list in place and frees
 * the original token values as needed.
 *
 * @param shell A pointer to the shell structure containing the token list
 *              and environment information.
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
			expanded = ft_expand_variables(current->value, shell->dup_env);
			if (current->quoted == 0)
				ft_handle_word_splitting(current, expanded);
			else
			{
				free(current->value);
				current->value = ft_strdup_safe(expanded);
			}
		}
		current = current->next;
	}
}
/**
 * @brief Handles word splitting in the shell after variable expansion.
 *
 * This function takes a token representing a word and a string containing the
 * expanded value, and splits the string into individual words. It then creates
 * new tokens for each split word and inserts them into the token list between
 * the given token and its next token. The original token's value is updated to
 * contain the first word. If the expanded string does not contain any spaces,
 * the original token's value is updated to contain the expanded string.
 *
 * @param shell A pointer to the shell structure containing the token list.
 * @param current A pointer to the token to be split.
 * @param expanded A string containing the expanded value of the token.
 */
static void	ft_handle_word_splitting(t_token *current, char *expanded)
{
	char	**split_words;
	t_token	*new_token;
	int		j;

	split_words = ft_split(expanded, ' ');
	if (split_words && split_words[1])
	{
		free(current->value);
		current->value = ft_strdup_safe(split_words[0]);
		j = 1;
		if (split_words && split_words[1])
		{
			free(current->value);
			current->value = ft_strdup_safe(split_words[0]);
			j = 1;
			while (split_words[j])
			{
				new_token = ft_create_token(ft_strdup_safe(split_words[j]), WORD);
				if (new_token)
				{
					new_token->quoted = 0;
					new_token->next = current->next;
					if (current->next)
						current->next->prev = new_token;
					current->next = new_token;
					new_token->prev = current;
					current = new_token;
				}
				j++;
			}
		}
		ft_free_arr(split_words);
		free(expanded);
	}
	else
	{
		free(current->value);
		current->value = ft_strdup_safe(expanded);
		if (split_words)
			ft_free_arr(split_words);
	}
}

/**
 * Expands all variables in the input string using the provided environment variables.
 *
 * This function iterates through the input string and identifies variables
 * prefixed by a dollar sign '$'. It supports both simple variable names and
 * variables enclosed in braces. For each variable found, it retrieves its value
 * from the environment array envp and replaces the variable with its value in
 * the result string.
 *
 * @param input The input string to process for variable expansion.
 * @param envp The environment array containing variable names and their values.
 *
 * @return A new string with all variables expanded. The caller is responsible
 * for freeing the returned string.
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
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) ||
			input[i + 1] == '_' || input[i + 1] == '{'))
			temp = ft_expand_variable(input, &i, envp);
		else
			temp = ft_append_char(result, input[i++]);
		if (result)
			free(result);
		result = ft_strdup_safe(temp);
	}
	return (result);
}
/**
 * Expand a single variable in a string.
 *
 * The variable is identified by its name, which is extracted from the input
 * string. The name is enclosed in curly braces if it contains special
 * characters. The variable value is retrieved from the environment array
 * \a envp.
 *
 * @param input The input string containing the variable name.
 * @param i The index of the character in \a input where the variable name
 * starts.
 * @param envp The environment array containing the variable value.
 *
 * @return The expanded variable value, or an empty string if the variable
 * name is not found in the environment array.
 */
static char	*ft_expand_variable(char *input, size_t *i, char **envp)
{
	char	*var_name;
	char	*var_value;
	size_t	start;
	int		braced;

	braced = 0;
	(*i)++;
	if (input[*i] == '{')
	{
		braced = 1;
		(*i)++;
	}
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_' ||
		(braced && input[*i] != '}')))
		(*i)++;
	if (braced && input[*i] == '}')
		(*i)++;
	else if (braced)
		return (ft_strdup_safe(""));
	var_name = ft_substr(input, start, *i - start - braced);
	var_value = ft_get_var_value(var_name, envp);
	free(var_name);
	if (!var_value)
		return (ft_strdup_safe(""));
	return (ft_strjoin("", var_value));
}

/**
 * Appends a single character to the end of a string, freeing the original string
 * in the process.
 *
 * @param result The string to append to.
 * @param c The character to append.
 *
 * @return The new string with the character appended.
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
