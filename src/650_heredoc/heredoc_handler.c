/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:19:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 16:23:20 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Handles a single heredoc redirection.
 *
 * Checks syntax validity for heredoc operator, creates a temporary file,
 * forks a child process to read the heredoc input and writes it to the
 * temporary file, waits for the child to finish, handles child exit status
 * and signals, processes the delimiter, and adds the temporary file to the
 * shell's list.
 *
 * @param shell The shell structure.
 * @param current The token containing the heredoc operator.
 * @return SUCCESS if the heredoc was handled successfully, ERROR otherwise.
 */
t_status	ft_handle_single_heredoc(t_shell *shell, t_token *current)
{
	char	*tempfile;
	pid_t	pid;
	int		status;

	if (ft_check_heredoc_syntax(current))
		return (ERROR);
	if (ft_create_temp_file(shell, &tempfile) == ERROR)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (perror(ERR_FORK_FAIL), ft_free(tempfile), ERROR);
	else if (pid == 0)
		ft_child_heredoc(shell, current->next, tempfile);
	else
	{
		waitpid(pid, &status, 0);
		if (ft_handle_child_exit(status, tempfile)
			|| ft_handle_child_signal(status, tempfile))
			return (ERROR);
		ft_process_delimiter(current, current->next, tempfile);
		ft_add_temp_file(shell, tempfile);
	}
	return (SUCCESS);
}
