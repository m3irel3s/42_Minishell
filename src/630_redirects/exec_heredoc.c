// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_heredoc.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
// /*   Updated: 2025/02/27 15:18:55 by meferraz         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// static char	*ft_expanded_line(t_shell *shell, char *line);
// static char	*create_temp_file(t_shell *shell);
// static void	add_temp_file(t_shell *shell, char *tempfile);
// static void	process_delimiter(t_token *current, t_token *delim, char *tempfile);

// /**
//  * @brief Processes all heredoc redirections in the token list.
//  *
//  * This function iterates through the token list, identifies heredoc tokens,
//  * reads input until the delimiter, stores the input in temporary files, and
//  * replaces the heredoc tokens with file input redirects to these temp files.
//  *
//  * @param shell The shell structure containing the token list.
//  */
// void	ft_process_heredocs(t_shell *shell)
// {
// 	t_token	*current;
// 	t_token	*delim;
// 	char	*delimiter;
// 	char	*tempfile;
// 	int		fd;

// 	current = shell->tokens;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 		{
// 			delim = current->next;
// 			if (!delim || (delim->type != ARG && delim->type != QUOTE))
// 			{
// 				ft_print_syntax_error("newline");
// 				shell->exit_status = 2;
// 				return ;
// 			}
// 			delimiter = delim->val.value;
// 			tempfile = create_temp_file(shell);
// 			if (!tempfile)
// 				return ;
// 			fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 			{
// 				perror("minishell");
// 				free(tempfile);
// 				return ;
// 			}
// 			read_heredoc_input(shell, delimiter, delim->quoted, fd);
// 			close(fd);
// 			process_delimiter(current, delim, tempfile);
// 			add_temp_file(shell, tempfile);
// 		}
// 		current = current->next;
// 	}
// }

// /**
//  * @brief Reads input for a heredoc and writes it to a file descriptor.
//  *
//  * @param shell The shell structure.
//  * @param delimiter The heredoc delimiter.
//  * @param quoted Whether the delimiter is quoted.
//  * @param fd The file descriptor to write the input to.
//  */
// void	read_heredoc_input(t_shell *shell, char *delimiter, int quoted, int fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (!quoted)
// 			line = ft_expanded_line(shell, line);
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// }

// /**
//  * @brief Creates a temporary file and returns its name.
//  *
//  * @param shell The shell structure.
//  * @return The name of the temporary file.
//  */
// static char	*create_temp_file(t_shell *shell)
// {
// 	char	*tempfile;
// 	int		fd;

// 	(void)shell;
// 	tempfile = ft_strdup("/tmp/minishell_heredoc_XXXXXX");
// 	if (!tempfile)
// 		return (NULL);
// 	fd = mkstemp(tempfile);
// 	if (fd == -1)
// 	{
// 		free(tempfile);
// 		return (NULL);
// 	}
// 	close(fd);
// 	return (tempfile);
// }

// /**
//  * @brief Adds a temporary file to the shell's list for cleanup.
//  *
//  * @param shell The shell structure.
//  * @param tempfile The name of the temporary file.
//  */
// static void	add_temp_file(t_shell *shell, char *tempfile)
// {
// 	char	**new_temp_files;
// 	int		i;

// 	i = 0;
// 	while (shell->temp_files && shell->temp_files[i])
// 		i++;
// 	new_temp_files = ft_safe_malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (shell->temp_files && shell->temp_files[i])
// 	{
// 		new_temp_files[i] = shell->temp_files[i];
// 		i++;
// 	}
// 	new_temp_files[i] = tempfile;
// 	new_temp_files[i + 1] = NULL;
// 	free(shell->temp_files);
// 	shell->temp_files = new_temp_files;
// }

// /**
//  * @brief Replaces a heredoc token with a file input redirect.
//  *
//  * @param current The heredoc token.
//  * @param delim The delimiter token.
//  * @param tempfile The temporary file name.
//  */
// static void	process_delimiter(t_token *current, t_token *delim, char *tempfile)
// {
// 	current->type = REDIRECT_IN;
// 	free(current->val.value);
// 	current->val.value = ft_strdup(tempfile);
// 	free(current->val.og_value);
// 	current->val.og_value = ft_strdup(tempfile);
// 	current->next = delim->next;
// 	if (delim->next)
// 		delim->next->prev = current;
// 	ft_free_token(delim);
// }

// /**
//  * @brief Cleans up all temporary files created for heredocs.
//  *
//  * @param shell The shell structure.
//  */
// void	ft_cleanup_temp_files(t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	if (!shell->temp_files)
// 		return ;
// 	while (shell->temp_files[i])
// 	{
// 		unlink(shell->temp_files[i]);
// 		free(shell->temp_files[i]);
// 		i++;
// 	}
// 	free(shell->temp_files);
// 	shell->temp_files = NULL;
// }

// /**
//  * @brief Expands a line of input by replacing '$' variables.
//  *
//  * @param shell The shell structure.
//  * @param line The input line to expand.
//  * @return The expanded line.
//  */
// static char	*ft_expanded_line(t_shell *shell, char *line)
// {
// 	char	*expanded;
// 	char	*tmp;
// 	size_t	i;

// 	expanded = ft_safe_strdup("");
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 		{
// 			tmp = ft_handle_dollar(shell, line, &i);
// 			if (tmp)
// 			{
// 				expanded = ft_safe_strjoin(expanded, tmp, 0);
// 				free(tmp);
// 			}
// 		}
// 		else
// 			expanded = ft_process_char(expanded, line[i++]);
// 	}
// 	free(line);
// 	return (expanded);
// }
