/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_build_prompt(char *user, char *cwd);

/**
 * @brief Returns a dynamically allocated string containing the shell's prompt.
 *
 * The prompt is built with the user's name, the current working directory, and
 * the current Git branch if applicable.
 *
 * @param shell A pointer to the shell structure.
 * @return A dynamically allocated string containing the shell's prompt.
 */
char	*ft_set_prompt(t_shell *shell)
{
	char	*cwd;
	char	*user;
	char	*prompt;

	if (!shell)
	{
		ft_print_error(ERR_INVALID_PARAMS);
		return (NULL);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_print_error(ERR_GET_CWD_FAIL);
		return (NULL);
	}
	user = getenv("USER");
	if (!user)
		user = "user";
	prompt = ft_build_prompt(user, cwd);
	free(cwd);
	return (prompt);
}

/**
 * @brief Constructs the shell prompt string.
 *
 * This function builds the shell prompt using the user's name, the current
 * working directory (shortened if possible), and the current Git branch if
 * applicable. The prompt is formatted with specific colors and symbols for
 * improved readability.
 *
 * @param shell A pointer to the shell structure.
 * @param user The name of the user to display in the prompt.
 * @param cwd The current working directory to display in the prompt.
 * @return A dynamically allocated string containing the formatted prompt.
 *         Returns NULL if memory allocation fails for any component.
 */
static char	*ft_build_prompt(char *user, char *cwd)
{
	char	*prompt;
	char	*short_cwd;
	char	*git_branch;

	short_cwd = ft_shorten_path(cwd);
	git_branch = ft_get_git_branch();
	if (!short_cwd)
		return (NULL);
	prompt = ft_safe_strjoin(BCYN2"┌─["BGRN2, user, 0);
	prompt = ft_safe_strjoin(prompt, BCYN2"]─["BYEL2, 1);
	prompt = ft_safe_strjoin(prompt, short_cwd, 1);
	prompt = ft_safe_strjoin(prompt, BCYN2"]", 1);
	free(short_cwd);
	if (git_branch)
	{
		prompt = ft_safe_strjoin(prompt, "─["BRED2, 1);
		prompt = ft_safe_strjoin(prompt, git_branch, 1);
		prompt = ft_safe_strjoin(prompt, BCYN2"]", 1);
		free(git_branch);
	}
	return (ft_safe_strjoin(prompt, "\n"BCYN2"└─$ "WHT2, 1));
}
