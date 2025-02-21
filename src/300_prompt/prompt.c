/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:04:18 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 09:52:44 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_build_prompt(t_shell *shell, char *user, const char *cwd);

char	*ft_set_prompt(t_shell *shell)
{
	char	*cwd;
	char	*user;
	char	*prompt;

	if (!shell)
		return (ft_handle_error(shell, ERR_INVALID_PARAMS));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_handle_error(shell, ERR_GET_CWD_FAIL));
	user = getenv("USER");
	if (!user)
		user = "user";
	prompt = ft_build_prompt(shell, user, cwd);
	free(cwd);
	return (prompt);
}

static char	*ft_build_prompt(t_shell *shell, char *user, const char *cwd)
{
	char	*prompt;
	char	*short_cwd;
	char	*git_branch;

	short_cwd = ft_shorten_path(shell, cwd);
	git_branch = ft_get_git_branch(shell);
	if (!short_cwd)
		return (NULL);
	prompt = ft_safe_join(shell, BCYN2"┌─["BGRN2, user, 0);
	prompt = ft_safe_join(shell, prompt, BCYN2"]─["BYEL2, 1);
	prompt = ft_safe_join(shell, prompt, short_cwd, 1);
	prompt = ft_safe_join(shell, prompt, BCYN2"]", 1);
	free(short_cwd);
	if (git_branch)
	{
		prompt = ft_safe_join(shell, prompt, "─["BRED2, 1);
		prompt = ft_safe_join(shell, prompt, git_branch, 1);
		prompt = ft_safe_join(shell, prompt, BCYN2"]", 1);
		free(git_branch);
	}
	return (ft_safe_join(shell, prompt, "\n"BCYN2"└─$ "WHT, 1));
}
