/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/27 17:11:16 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_expanded_line(t_shell *shell, char *line);
static char	*ft_create_temp_file(t_shell *shell);
static void	ft_add_temp_file(t_shell *shell, char *tempfile);
static void	ft_process_delimiter(t_token *current, t_token *delim,
				char *tempfile);
void		ft_read_heredoc_input(t_shell *shell, char *delimiter, int quoted,
				int fd);

/**
 * @brief Process all heredoc tokens in the token list.
 *
 * Process all heredoc tokens in the token list, creating temporary files
 * for each one and reading user input until the delimiter is found.
 *
 * @param shell The shell structure containing the token list.
 */
void	ft_process_heredocs(t_shell *shell)
{
	t_token	*current;
	t_token	*delim;
	char	*tempfile;
	int		fd;

	current = shell->tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			delim = current->next;
			if (!delim || (delim->type != WORD && !delim->quoted))
			{
				ft_print_syntax_error("newline");
				g_exit_status = EXIT_FAILURE;
				return ;
			}
			tempfile = ft_create_temp_file(shell);
			if (!tempfile)
				return ;
			fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("minishell");
				free(tempfile);
				return ;
			}
			ft_read_heredoc_input(shell, delim->val.value, delim->quoted, fd);
			close(fd);
			ft_process_delimiter(current, delim, tempfile);
			ft_add_temp_file(shell, tempfile);
		}
		current = current->next;
	}
}

void	ft_read_heredoc_input(t_shell *shell, char *delimiter, int quoted, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!quoted)
			line = ft_expanded_line(shell, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

/**
 * @brief Generates a unique temporary filename for heredoc.
 *
 * Generates a unique temporary filename for heredoc, in the form of
 * "/tmp/minishell_heredoc_<number>".
 *
 * @return The generated temporary filename.
 */
static char	*ft_generate_temp_filename(void)
{
	static int	counter = 0;
	char		*prefix;
	char		*counter_str;
	char		*tempfile;
	size_t		len;

	prefix = "/tmp/minishell_heredoc_";
	counter_str = ft_itoa(counter);
	if (!counter_str)
		return (NULL);
	len = ft_strlen(prefix) + ft_strlen(counter_str) + 1;
	tempfile = ft_safe_malloc(len);
	if (!tempfile)
	{
		free(counter_str);
		return (NULL);
	}
	ft_strlcpy(tempfile, prefix, len);
	ft_strlcat(tempfile, counter_str, len);
	free(counter_str);
	counter++;
	return (tempfile);
}

static char	*ft_create_temp_file(t_shell *shell)
{
	char	*tempfile;
	int		fd;
	int		i;

	(void)shell;
	i = 0;
	while (i < 100)
	{
		tempfile = ft_generate_temp_filename();
		if (!tempfile)
			return (NULL);
		fd = open(tempfile, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd != -1)
		{
			close(fd);
			return (tempfile);
		}
		free(tempfile);
		if (errno != EEXIST)
		{
			perror("minishell");
			return (NULL);
		}
		i++;
	}
	ft_printf(STDERR_FILENO, "minishell: could not create a unique temp file\n");
	return (NULL);
}

static void	ft_add_temp_file(t_shell *shell, char *tempfile)
{
	char	**new_temp_files;
	int		i;

	i = 0;
	while (shell->temp_files && shell->temp_files[i])
		i++;
	new_temp_files = ft_safe_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell->temp_files && shell->temp_files[i])
	{
		new_temp_files[i] = shell->temp_files[i];
		i++;
	}
	new_temp_files[i] = tempfile;
	new_temp_files[i + 1] = NULL;
	free(shell->temp_files);
	shell->temp_files = new_temp_files;
}

static void	ft_process_delimiter(t_token *current, t_token *delim, char *tempfile)
{
	t_token	*filename_token;

	current->type = REDIRECT_IN;
	free(current->val.value);
	current->val.value = ft_safe_strdup("");
	free(current->val.og_value);
	current->val.og_value = ft_safe_strdup("");
	filename_token = ft_safe_malloc(sizeof(t_token));
	if (!filename_token)
		return ;
	filename_token->type = WORD;
	filename_token->val.value = ft_safe_strdup(tempfile);
	filename_token->val.og_value = ft_safe_strdup(tempfile);
	filename_token->quoted = 0;
	filename_token->prev = current;
	filename_token->next = delim->next;
	current->next = filename_token;
	if (delim->next)
		delim->next->prev = filename_token;
	ft_free_token(delim);
}

void	ft_cleanup_temp_files(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->temp_files)
		return ;
	while (shell->temp_files[i])
	{
		unlink(shell->temp_files[i]);
		free(shell->temp_files[i]);
		i++;
	}
	free(shell->temp_files);
	shell->temp_files = NULL;
}

static char	*ft_expanded_line(t_shell *shell, char *line)
{
	char	*expanded;
	char	*tmp;
	size_t	i;

	expanded = ft_safe_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = ft_handle_dollar(shell, line, &i);
			if (tmp)
			{
				expanded = ft_safe_strjoin(expanded, tmp, 0);
				free(tmp);
			}
		}
		else
			expanded = ft_process_char(expanded, line[i++]);
	}
	free(line);
	return (expanded);
}
