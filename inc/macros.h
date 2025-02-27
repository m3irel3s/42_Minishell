/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/27 15:15:30 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

//============================================================================//
//                              EXIT STATUS CODES                             //
//============================================================================//
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_MISUSE 2
# define EXIT_CANNOT_EXECUTE 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_INVALID_EXIT_ARG 128
# define EXIT_FATAL_SIGNAL 128

# define ERR_EXIT_NUM_REQ \
	"minishell: exit: %s: numeric argument required\n"
# define ERR_EXIT_TOO_MANY_ARGS \
	"minishell: exit: too many arguments\n"

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
# define ERR_SYNTAX_VALIDATION_FAIL \
    "minishell: Syntax validation failed\n"

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
# define ERR_REDIR_OPEN_FAIL \
    "minishell: Failed to open file: %s\n"

//============================================================================//
//                          COMMAND ERROR MESSAGES                            //
//============================================================================//
# define ERR_CMD_NOT_FOUND \
    "minishell: %s: command not found\n"
# define ERR_CMD_INVALID_OPT \
    "minishell: %s: invalid option\n"
# define ERR_CMD_TOO_MANY_ARGS \
    "minishell: %s: too many arguments\n"
# define ERR_HOME_NOT_SET \
    "minishell: cd: HOME not set\n"
# define ERR_OLDPWD_NOT_SET \
    "minishell: cd: OLDPWD not set\n"
# define ERR_CD_FAIL \
    "minishell: cd: %s: No such file or directory\n"

//============================================================================//
//                           GENERAL ERROR MESSAGES                           //
//============================================================================//
# define ERR_INVALID_PARAMS \
    "minishell: Invalid parameters\n"
# define ERR_INVALID_SHELL_OR_INPUT \
    "minishell: Invalid shell or input\n"
# define ERR_INVALID_REDIRECT_TYPE \
    "minishell: Invalid redirection type\n"
# define ERR_DUP_FAIL \
    "minishell: Failed to duplicate file descriptor\n"
# define ERR_DUP2_FAIL \
    "minishell: Failed to redirect file descriptor\n"

//============================================================================//
//                        INITIALIZATION ERROR MESSAGES                       //
//============================================================================//
# define ERR_ENV_DUP_FAIL \
    "minishell: Failed to duplicate environment\n"
# define ERR_GET_CWD_FAIL \
    "minishell: Failed to get current working directory\n"
# define ERR_SHELL_INIT_FAIL \
    "minishell: Failed to initialize shell\n"

//============================================================================//
//                           SAFE FUNCTIONS ERROR MESSAGES                    //
//============================================================================//
# define ERR_INVALID_ALLOC_SIZE \
    "minishell: Error: Invalid allocation size <= 0.\n"
# define ERR_MALLOC_FAIL \
    "minishell: fatal error: memory allocation failed\n"
# define ERR_INVALID_PROMPT \
    "minishell: invalid prompt\n"
# define ERR_STRJOIN_FAIL \
    "minishell: String join operation failed\n"

//============================================================================//
//                           SIGNAL ERROR MESSAGES                            //
//============================================================================//
# define ERR_SIGNAL_SETUP_INT \
    "minishell: Error setting up SIGINT handler\n"
# define ERR_SIGNAL_SETUP_QUIT \
    "minishell: Error setting up SIGQUIT handler\n"
# define ERR_SIGNAL_SETUP_FAIL \
    "minishell: Failed to set up signal handlers\n"

# define ERR_OPEN_FAIL "minishell: Error opening file\n"
# define ERR_STRDUP_FAIL "minishell: Failed to duplicate string\n"

# define ERR_TOKENIZATION_FAIL "minishell: Failed to tokenize input\n"
# define ERR_EXPANSION_FAIL "minishell: Failed to expand variables\n"

# define ERR_OPERATOR_HANDLING_FAIL "minishell: Failed to handle operator\n"
# define ERR_EXPORT_TOKEN_FAIL "minishell: Failed to create export token\n"
# define ERR_EXPORT_ARG_HANDLING_FAIL "minishell: Failed to handle \
    export argument\n"
# define ERR_WORD_HANDLING_FAIL "minishell: Failed to handle word\n"
# define ERR_TOKEN_CREATION_FAIL "minishell: Failed to create token\n"
# define ERR_NULL_TOKEN_VALUE "minishell: Error: Null token value\n"
# define ERR_SUBSTR_FAIL "minishell: Substring creation failed\n"
# define ERR_PIPE_FAIL "minishell: error creating heredoc pipe\n"
# define ERR_WRITE_FAIL "minishell: error writing to heredoc pipe\n"
# define ERR_INVALID_SHELL "minishell: Invalid shell structure\n"
# define ERR_FORK_FAIL "minishell: fork failed\n"
# define ERR_EXPORT_INVALID_IDENTIFIER \
    "export: %s: not a valid identifier\n"
# define ERR_WORD_COUNT_FAIL "minishell: Failed to count words in input\n"

#endif
