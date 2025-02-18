/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 08:23:56 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

//============================================================================//
//                               ERROR MESSAGES                               //
//============================================================================//

# define ERR_UNMATCHED_QUOTE \
	"minishell: syntax error: unmatched quote\n"
# define ERR_REDIRECT_NO_FILE \
	"minishell: syntax error near unexpected token `newline'\n"
# define ERR_REDIRECT_SYNTAX \
	"minishell: syntax error near unexpected token `%s`\n"
# define ERR_UNEXPECTED_TOKEN \
	"minishell: syntax error near unexpected token `%s`\n"
# define ERR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define ERR_HEREDOC_EOF \
	"minishell: warning: here-document at line %d delimited by " \
	"end-of-file (wanted `%s`)\n"
# define ERR_HEREDOC_INVALID_DELIMITER \
	"minishell: syntax error near unexpected token `newline'\n"
# define ERR_UNEXPECTED_EOF \
	"minishell: syntax error near unexpected token `newline'\n"
# define ERR_CD_NOT_IN_PWD "cd: string not in pwd: %s\n"
# define ERR_CD_NO_SUCH_FILE "cd: no such file or directory: %s\n"
# define ERR_EXPORT_INVALID_ID "export: `%s`: not a valid identifier\n"


#endif
