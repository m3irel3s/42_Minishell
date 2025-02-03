/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/03 09:25:48 by meferraz         ###   ########.fr       */
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

//============================================================================//
//                                STRUCTURES                                  //
//============================================================================//

typedef struct s_shell
{
	char			**envp;
	char			*prompt;
	char			*input;
	t_token_array	*tokens;
}	t_shell;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

typedef struct s_token_array
{
	t_token	**tokens;
	size_t	size;
}	t_token_array;

#endif