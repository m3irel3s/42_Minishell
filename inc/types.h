/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:15:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/12 14:24:27 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

//============================================================================//
//                                  ENUMS                                     //
//============================================================================//

typedef enum e_status
{
	SUCCESS = 0,
	ERROR = 1
}	t_status;

typedef enum e_path_type
{
	PATH_EXECUTABLE,
	PATH_NOT_EXECUTABLE,
	PATH_NOT_FOUND
}	t_path_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	ERROR_TOKEN
}	t_token_type;

typedef enum e_cmd_type
{
	CMD_AUTHORS,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXEC,
	CMD_UNKNOWN
}	t_cmd_type;

//============================================================================//
//                                STRUCTURES                                  //
//============================================================================//

typedef struct s_pipe
{
	int	read_fd;
	int	write_fd;
}	t_pipe;

typedef struct s_token_val
{
	char			*value;
	char			*og_value;
}	t_token_val;

typedef struct s_token
{
	t_token_val		val;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_quote_info
{
	int		in_quotes;
	char	quote_char;
	int		quoted;
}	t_quote_info;

typedef struct s_redirect
{
	t_token_type		type;
	char				*filename;
	int					quoted;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_terminal
{
	struct termios	og_termios;
	int				is_terminal;
}	t_terminal;

typedef struct s_shell
{
	char			**env_cpy;
	char			*last_cwd;
	char			*prompt;
	char			*input;
	t_token			*tokens;
	t_redirect		*redirects;
	char			**temp_files;
	int				redirected_stdin;
	int				redirected_stdout;
	int				in_export;
	size_t			random_number;
	t_terminal		*tml;
}	t_shell;

typedef struct s_g
{
	int		g_exit_status;
	int		g_og_stdout;
}	t_g;

//============================================================================//
//                                GLOBAL VARIABLE                             //
//============================================================================//

extern t_g	g_gbl;

#endif
