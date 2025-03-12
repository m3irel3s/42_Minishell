/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:20 by meferraz         ###   ########.fr       */
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
		if (shell->last_cwd)
			cwd = ft_strdup(shell->last_cwd);
		if (!cwd)
			return (ft_print_error(ERR_GET_CWD_FAIL), NULL);
	}
	user = getenv("USER");
	if (!user)
		user = "user";
	prompt = ft_build_prompt(user, cwd);
	ft_free(cwd);
	shell->tml = ft_safe_calloc(sizeof(t_terminal));
	return (prompt);
}

/**
 * @brief Constructs a custom, visually enhanced shell prompt.
 *
 * This function builds a colorful prompt showing the user's name, a shortened
 * current working directory, and (if applicable) the current Git branch. The
 * prompt now uses stylish symbols and background colors (via macros like BBGRN2)
 * to create an eye‐catching one‑line display.
 *
 * @param user The name of the user to display in the prompt.
 * @param cwd The current working directory to display in the prompt.
 * @return A dynamically allocated string containing the formatted prompt.
 *         Returns NULL if any memory allocation fails.
*/
static char	*ft_build_prompt(char *user, char *cwd)
{
	char	*prompt;
	char	*short_cwd;
	char	*git_branch;

	short_cwd = ft_shorten_path(cwd);
	git_branch = ft_get_git_branch();
	prompt = ft_safe_strjoin(RS BG_G "❖ " MGT, user, 0);
	prompt = ft_safe_strjoin(prompt, RS " ", 1);
	prompt = ft_safe_strjoin(prompt, BG_B "⌂ " YLW, 1);
	prompt = ft_safe_strjoin(prompt, short_cwd, 1);
	prompt = ft_safe_strjoin(prompt, RS " ", 1);
	if (git_branch)
	{
		prompt = ft_safe_strjoin(prompt, BG_M " ❦ " GRN2, 1);
		prompt = ft_safe_strjoin(prompt, git_branch, 1);
		prompt = ft_safe_strjoin(prompt, RS " ", 1);
		ft_free(git_branch);
	}
	prompt = ft_safe_strjoin(prompt, WHT2 "❯ " RS, 1);
	ft_free(short_cwd);
	return (prompt);
}
