/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/03 14:53:13 by meferraz         ###   ########.fr       */
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

typedef enum e_quote_state
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_state;

//============================================================================//
//                                STRUCTURES                                  //
//============================================================================//

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	char			**envp;
	char			*prompt;
	char			*input;
	t_token			*tokens;
}	t_shell;

#endif
