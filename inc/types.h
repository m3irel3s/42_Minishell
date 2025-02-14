/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 10:31:56 by jmeirele         ###   ########.fr       */
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

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_cmd_type
{
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

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redirect
{
	t_token_type		type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_shell
{
	char			**dup_env;
	char			*prompt;
	char			*input;
	t_token			*tokens;
	t_redirect		*redirects;
	int				in_export;
} t_shell;

#endif
