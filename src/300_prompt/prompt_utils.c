/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:00:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 10:03:57 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

/**
 * @brief Handles an error by printing an error message and setting the shell's
 * exit status to EXIT_FAILURE.
 *
 * @param shell The shell structure to update the exit status.
 * @param error_msg The error message to print to the standard error stream.
 * @return Always returns NULL, indicating that an error occurred.
 */
char	*ft_handle_error(t_shell *shell, char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
	return (NULL);
}

/**
 * @brief A safe version of ft_strjoin that handles errors and frees the first
 * string if requested.
 *
 * This function is similar to ft_strjoin, but it checks for errors and frees
 * the first string if requested. If the memory allocation fails, it sets the
 * shell's exit status to EXIT_FAILURE and returns NULL.
 *
 * @param shell The shell structure.
 * @param s1 The first string to join.
 * @param s2 The second string to join.
 * @param free_s1 A flag indicating whether to free the first string.
 * @return The joined string, or NULL if there was an error.
 */
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
