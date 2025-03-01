/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 14:58:42 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Retrieves the current git branch from a .git/HEAD file.
 *
 * Opens the .git/HEAD file and reads its contents into a buffer. If the file
 * exists and its contents start with "ref: refs/heads/", extracts the branch
 * name from the buffer and returns it as a dynamically allocated string.
 *
 * @param shell The shell structure.
 * @return The current git branch name as a string, or NULL if there was an
 * error or the file does not exist.
 */
char	*ft_get_git_branch(void)
{
	char	buffer[1024];
	int		fd;
	ssize_t	bytes_read;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd == -1)
	{
		ft_print_error("");
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
		return (ft_safe_strdup(buffer + 16));
	}
	return (NULL);
}

/**
 * @brief Shortens a path string by replacing the home directory with a tilde.
 *
 * If the path starts with the home directory, replaces it with a tilde. If not,
 * returns a copy of the path.
 *
 * @param shell The shell structure.
 * @param path The path to shorten.
 * @return The shortened path string, or NULL if there was an error.
 */
char	*ft_shorten_path(char *path)
{
	char	*home;
	char	*short_path;

	home = getenv("HOME");
	if (home && ft_strncmp(path, home, ft_strlen(home)) == 0)
		short_path = ft_safe_strjoin("~", path + ft_strlen(home), 0);
	else
		short_path = ft_safe_strdup(path);
	if (!short_path)
		return (ft_print_error(ERR_STRDUP_FAIL), NULL);
	return (short_path);
}
