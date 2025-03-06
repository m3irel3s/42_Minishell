/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tempfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:15:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 16:19:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Generates a unique temporary filename for heredoc usage.
 *
 * This function creates a unique filename for a temporary file used
 * during heredoc processing. The filename is generated using a static
 * counter, which is initialized from the shell's random number, and
 * follows the pattern "/tmp/minishell_heredoc_<number>". It increments
 * the counter after each use to ensure uniqueness. The generated
 * filename is allocated and returned through the `tempfile` parameter.
 *
 * @param shell The shell structure containing the random number used
 *              for the initial counter value.
 * @param tempfile A pointer to a string where the generated filename
 *                 will be stored.
 * @return SUCCESS if the filename was generated successfully, ERROR
 *         if a memory allocation error occurred.
 */
static t_status	ft_generate_temp_filename(t_shell *shell, char **tempfile)
{
	static int	counter;
	char		*prefix;
	char		*counter_str;
	size_t		len;

	counter = shell->random_number;
	prefix = "/tmp/minishell_heredoc_";
	counter_str = ft_itoa(counter);
	if (!counter_str)
		return (ERROR);
	len = ft_strlen(prefix) + ft_strlen(counter_str) + 1;
	*tempfile = ft_safe_calloc(len);
	if (!*tempfile)
		return (ft_free(counter_str), ERROR);
	ft_strlcpy(*tempfile, prefix, len);
	ft_strlcat(*tempfile, counter_str, len);
	ft_free(counter_str);
	counter++;
	shell->random_number = counter;
	return (SUCCESS);
}

/**
 * @brief Creates a unique temporary file for heredoc.
 *
 * Attempts to generate a unique temporary filename and checks its existence.
 * If the filename does not exist, it is considered unique and the function
 * returns SUCCESS. If a unique filename cannot be generated within 1000
 * attempts, an error message is printed and the function returns ERROR.
 *
 * @param shell The shell structure used to generate and store the filename.
 * @param tempfile A pointer to store the generated unique filename.
 * @return SUCCESS if a unique filename is created, otherwise ERROR.
 */

static t_status	ft_create_temp_file(t_shell *shell, char **tempfile)
{
	int	i;

	i = 0;
	while (i < 1000)
	{
		if (ft_generate_temp_filename(shell, tempfile) == ERROR)
			return (ERROR);
		if (access(*tempfile, F_OK) != 0)
			return (SUCCESS);
		ft_free(*tempfile);
		*tempfile = NULL;
		i++;
	}
	ft_printf(STDERR_FILENO, ERR_TEMP_FILE);
	return (ERROR);
}

/**
 * @brief Adds a temporary file to the shell's list of temporary files.
 *
 * Allocates memory to store an additional temporary file in the shell's
 * `temp_files` array. Copies existing temporary file paths to the new
 * array, appends the new temporary file, and updates the shell's
 * `temp_files` pointer to the new array.
 *
 * @param shell The shell structure to update with a new temporary file.
 * @param tempfile The path of the temporary file to add to the shell's list.
 */
static void	ft_add_temp_file(t_shell *shell, char *tempfile)
{
	char	**new_temp_files;
	int		i;

	i = 0;
	while (shell->temp_files && shell->temp_files[i])
		i++;
	new_temp_files = ft_calloc(i + 2, sizeof(char *));
	if (!new_temp_files)
		return ;
	i = 0;
	while (shell->temp_files && shell->temp_files[i])
	{
		new_temp_files[i] = shell->temp_files[i];
		i++;
	}
	new_temp_files[i] = tempfile;
	ft_free(shell->temp_files);
	shell->temp_files = new_temp_files;
}
