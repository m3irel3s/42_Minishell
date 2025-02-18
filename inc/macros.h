/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 09:16:28 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

//============================================================================//
//                            SYNTAX ERROR MESSAGES                           //
//============================================================================//
# define ERR_SYNTAX_UNEXPECTED_TOKEN \
	"minishell: syntax error near unexpected token `%s'\n"
# define ERR_SYNTAX_UNCLOSED_QUOTE \
	"minishell: syntax error: unmatched quotes detected\n"
# define ERR_SYNTAX_EOF_REDIR \
	"minishell: syntax error: redirection at end of input\n"
# define ERR_SYNTAX_EOF_PIPE \
	"minishell: syntax error: pipe at end of input\n"
# define ERR_SYNTAX_EOF_HEREDOC \
	"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"

//============================================================================//
//                         REDIRECTION ERROR MESSAGES                         //
//============================================================================//
# define ERR_REDIR_AMBIGUOUS \
	"minishell: %s: ambiguous redirect\n"
# define ERR_REDIR_NO_FILE \
	"minishell: %s: No such file or directory\n"
# define ERR_REDIR_IS_DIR \
	"minishell: %s: Is a directory\n"
# define ERR_REDIR_PERM_DENIED \
	"minishell: %s: Permission denied\n"

//============================================================================//
//                          COMMAND ERROR MESSAGES                            //
//============================================================================//
# define ERR_CMD_NOT_FOUND \
	"minishell: %s: command not found\n"
# define ERR_CMD_INVALID_OPT \
	"minishell: %s: invalid option\n"
# define ERR_CMD_TOO_MANY_ARGS \
	"minishell: %s: too many arguments\n"

//============================================================================//
//                          BUILTIN ERROR MESSAGES                            //
//============================================================================//
# define ERR_CD_NO_HOME \
	"minishell: cd: HOME not set\n"
# define ERR_CD_NO_OLDPWD \
	"minishell: cd: OLDPWD not set\n"
# define ERR_CD_NOT_FOUND \
	"minishell: cd: %s: No such file or directory\n"
# define ERR_CD_NOT_DIR \
	"minishell: cd: %s: Not a directory\n"

# define ERR_EXPORT_INVALID_ID \
	"minishell: export: `%s': not a valid identifier\n"
# define ERR_UNSET_INVALID_ID \
	"minishell: unset: `%s': not a valid identifier\n"

# define ERR_EXIT_NON_NUM \
	"minishell: exit: %s: numeric argument required\n"
# define ERR_EXIT_TOO_MANY_ARGS \
	"minishell: exit: too many arguments\n"

//============================================================================//
//                          PERMISSION ERROR MESSAGES                         //
//============================================================================//
# define ERR_PERM_ISDIR \
	"minishell: %s: Is a directory\n"
# define ERR_PERM_DENIED \
	"minishell: %s: Permission denied\n"

//============================================================================//
//                          HEREDOC ERROR MESSAGES                            //
//============================================================================//
# define ERR_HEREDOC_CTRL_C \
	"minishell: warning: here-document at line %d interrupted\n"
# define ERR_HEREDOC_EOF \
	"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"

//============================================================================//
//                           MISC ERROR MESSAGES                              //
//============================================================================//
# define ERR_MALLOC_FAIL \
	"minishell: fatal error: memory allocation failed\n"
# define ERR_FORK_FAIL \
	"minishell: fatal error: fork failed\n"
# define ERR_PIPE_FAIL \
	"minishell: fatal error: pipe creation failed\n"

#endif
