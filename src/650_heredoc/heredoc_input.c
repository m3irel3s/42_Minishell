/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:15:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/10 21:22:14 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status	ft_fork_heredoc(pid_t *pid, t_shell *shell, t_token *delim,
					char *tempfile);
static t_status	ft_handle_heredoc_parent(pid_t pid, char *tempfile,
					t_shell *shell, t_token *current, int is_terminal,
					struct termios original_termios);
static void		ft_child_heredoc(t_shell *shell, t_token *delim,
					char *tempfile);

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
	char				*tempfile;
	pid_t				pid;
	struct sigaction	sa_ignore;
	struct sigaction	sa_old;
	struct termios		original_termios;
	int					is_terminal;

	is_terminal = isatty(STDIN_FILENO);
	if (ft_check_heredoc_syntax(current) == ERROR)
		return (ERROR);
	if (ft_create_temp_file(shell, &tempfile) == ERROR)
		return (ERROR);
	if (is_terminal && tcgetattr(STDIN_FILENO, &original_termios) == -1)
		return (ft_free(tempfile), ft_print_error(ERR_TCGETATTR), ERROR);
	if (ft_setup_sigint_ignore(&sa_ignore, &sa_old) == ERROR)
		return (ft_free(tempfile), ERROR);
	if (ft_fork_heredoc(&pid, shell, current->next, tempfile) == ERROR)
		return (sigaction(SIGINT, &sa_old, NULL), ft_free(tempfile), ERROR);
	return (ft_handle_heredoc_parent(pid, tempfile, shell, current, is_terminal, original_termios));
}

/**
 * @brief Forks a new process for handling heredoc input.
 *
 * This function attempts to create a child process using fork. If the
 * fork operation fails, an error is reported and the temporary file
 * is freed. In the child process, it calls ft_child_heredoc to handle
 * the heredoc input. The parent process continues execution.
 *
 * @param pid Pointer to store the process ID of the forked child.
 * @param shell The shell structure containing relevant context.
 * @param delim The token containing the heredoc delimiter.
 * @param tempfile The name of the temporary file to write heredoc input.
 * @return SUCCESS if fork succeeded, ERROR if fork failed.
 */

static t_status	ft_fork_heredoc(pid_t *pid, t_shell *shell,
		t_token *delim, char *tempfile)
{
	*pid = fork();
	if (*pid == -1)
		return (ft_print_error(ERR_FORK_FAIL), ft_free(tempfile), ERROR);
	else if (*pid == 0)
		ft_child_heredoc(shell, delim, tempfile);
	return (SUCCESS);
}

/**
 * @brief Handles the parent process after forking for heredoc input.
 *
 * This function waits for the child process to finish and handles its
 * exit status and signals. It then processes the heredoc delimiter and
 * adds the temporary file containing the heredoc input to the shell's
 * list of temporary files.
 *
 * @param pid The process ID of the forked child process.
 * @param tempfile The name of the temporary file to write heredoc input.
 * @param shell The shell structure containing relevant context.
 * @param current The token containing the heredoc operator.
 * @return SUCCESS if the heredoc was handled successfully, ERROR otherwise.
 */
static t_status	ft_handle_heredoc_parent(pid_t pid, char *tempfile,
		t_shell *shell, t_token *current, int is_terminal, struct termios original_termios)
{
	int					status;
	struct sigaction	sa_old;

	waitpid(pid, &status, 0);
	if (is_terminal && tcsetattr(STDIN_FILENO, TCSANOW, &original_termios) == -1)
		return (ft_print_error(ERR_TCGETATTR), ft_free(tempfile), ERROR);
	if (sigaction(SIGINT, &sa_old, NULL) == -1)
	{
		ft_print_error("sigaction restore failed");
		ft_free(tempfile);
		return (ERROR);
	}
	if (ft_handle_child_exit(status, tempfile) == ERROR
		|| ft_handle_child_signal(status, tempfile) == ERROR)
		return (ERROR);
	ft_process_delimiter(current, current->next, tempfile);
	ft_add_temp_file(shell, tempfile);
	return (SUCCESS);
}

/**
 * @brief Handles the child process for heredoc input.
 *
 * This function is executed by the child process after forking in
 * ft_fork_heredoc. It sets up the child process to ignore SIGINT
 * and SIGQUIT, opens the temporary file to write heredoc input,
 * reads the input using ft_read_heredoc_input, and then closes the
 * file descriptor and exits the child process.
 *
 * @param shell The shell structure containing relevant context.
 * @param delim The token containing the heredoc delimiter.
 * @param tempfile The name of the temporary file to write heredoc input.
 */
static void	ft_child_heredoc(t_shell *shell, t_token *delim, char *tempfile)
{
	struct sigaction	sa;
	int					fd;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_print_error(ERR_OPEN_FAIL);
		ft_free(tempfile);
		exit(g.g_exit_status);
	}
	ft_free(tempfile);
	ft_read_heredoc_input(shell, delim->val.value, delim->quoted, fd);
	close(fd);
	g.g_exit_status = EXIT_SUCCESS;
	exit(g.g_exit_status);
}
