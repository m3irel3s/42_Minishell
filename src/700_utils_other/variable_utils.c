/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:40:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 14:54:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Returns the length of a string composed by str1 and str2.
 *
 * This function is used to know the length of a string that is the result
 * of the concatenation of two strings.
 *
 * @param str1 The first string.
 * @param str2 The second string.
 * @return The length of the concatenated string.
 */
int	ft_get_str_length(char *str1, char *str2)
{
	return (ft_strlen(str1) + ft_strlen(str2));
}

/**
 * @brief Retrieves the value of a given environment variable.
 *
 * This function searches the provided environment array for a variable
 * matching the specified name. If found, it returns a pointer to the
 * variable's value. If the variable is not found or does not have an
 * associated value, an empty string is returned.
 *
 * @param var The name of the environment variable to search for.
 * @param env The environment array to search within.
 * @return A pointer to the value of the environment variable, or an
 * empty string if not found.
 */
char	*ft_get_var_value(char *var, char **env)
{
	int		i;
	char	*to_compare;

	i = 0;
	while (env[i])
	{
		to_compare = ft_get_var_name(env[i]);
		if (ft_strcmp(to_compare, var) == SUCCESS && ft_strchr(env[i], '='))
			return (ft_free(to_compare), env[i] + ft_strlen(var) + 1);
		i++;
		ft_free(to_compare);
	}
	return ("");
}

/**
 * @brief Returns the index of the variable in the environment array.
 *
 * This function searches the provided environment array for a variable
 * matching the specified name. If found, it returns the index of the
 * variable in the array. If the variable is not found, -1 is returned.
 *
 * @param var The name of the environment variable to search for.
 * @param env The environment array to search within.
 * @return The index of the environment variable in the array, or -1 if
 * not found.
 */
int	ft_get_var_index(char *var, char **env)
{
	int		i;
	char	*to_compare;

	i = 0;
	while (env[i])
	{
		to_compare = ft_get_var_name(env[i]);
		if (ft_strcmp(to_compare, var) == SUCCESS)
			return (ft_free(to_compare), i);
		i++;
		ft_free(to_compare);
	}
	return (-1);
}

/**
 * @brief Returns a pointer to the name of an environment variable.
 *
 * This function takes a string representing an environment variable and
 * returns a pointer to the name of the variable. The returned string is
 * dynamically allocated and should be freed after use.
 *
 * @param str The string representing the environment variable.
 * @return A pointer to the name of the environment variable, or NULL if
 * memory allocation fails.
 */
char	*ft_get_var_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	res = ft_safe_calloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
