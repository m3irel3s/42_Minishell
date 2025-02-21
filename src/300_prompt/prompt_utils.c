/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 09:53:38 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_get_git_branch(t_shell *shell)
{
	char	buffer[1024];
	int		fd;
	ssize_t	bytes_read;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(ERR_OPEN_FAIL, STDERR_FILENO);
		shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (ft_strncmp(buffer, "ref: refs/heads/", 16) == 0)
	{
		buffer[ft_strchr(buffer, '\n') - buffer] = '\0';
		return (ft_strdup(buffer + 16));
	}
	return (NULL);
}

char	*ft_shorten_path(t_shell *shell, const char *path)
{
	char	*home;
	char	*short_path;

	home = getenv("HOME");
	if (home && ft_strncmp(path, home, ft_strlen(home)) == 0)
		short_path = ft_strjoin("~", path + ft_strlen(home));
	else
		short_path = ft_strdup(path);
	if (!short_path)
		return (ft_handle_error(shell, ERR_STRDUP_FAIL));
	return (short_path);
}

char	*ft_handle_error(t_shell *shell, char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
	return (NULL);
}

char	*ft_safe_join(t_shell *shell, char *s1, char *s2, int free_s1)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	if (!result)
		return (ft_handle_error(shell, ERR_STRJOIN_FAIL));
	return (result);
}
