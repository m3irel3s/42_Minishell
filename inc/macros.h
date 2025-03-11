/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/11 14:40:34 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

//============================================================================//
//                              EXIT STATUS CODES                             //
//============================================================================//
# define EXIT_SUCCESS          0    // Successful execution
# define EXIT_FAILURE          1    // General failure
# define EXIT_MISUSE           2    // Misuse of shell builtin
# define EXIT_IS_A_DIRECTORY   126  // Is a directory
# define EXIT_PERM_DENIED      126  // Command cannot be executed
									// (e.g., permission denied)
# define EXIT_CMD_NOT_FOUND    127  // Command not found
# define EXIT_NO_SUCH_FILE     127  // No such file or directory
# define EXIT_INVALID_EXIT_ARG 128  // Invalid argument to exit builtin
# define EXIT_FATAL_SIGNAL     128  // Fatal signal received
									// (overlaps with INVALID_EXIT_ARG)
# define EXIT_SIGINT           130  // Interrupted by SIGINT (Ctrl+C)
# define EXIT_SIGQUIT          131  // Quit by SIGQUIT (Ctrl+\)

//============================================================================//
//                            ERROR MESSAGES - GENERAL                        //
//============================================================================//
# define ERR_CMD_NOT_FOUND         "minishell: %s: command not found\n"
# define ERR_PERM_DENIED           "minishell: %s: Permission denied\n"
# define ERR_IS_A_DIRECTORY        "minishell: %s: Is a directory\n"
# define ERR_NO_SUCH_FILE          "minishell: %s: No such file or directory\n"
# define ERR_DUP2_FAIL             "minishell: Failed to redirect file \
descriptor\n"
# define ERR_FORK_FAIL             "minishell: fork failed\n"
# define ERR_INVALID_PARAMS        "minishell: Invalid parameters\n"
# define ERR_INVALID_SHELL_OR_INPUT "minishell: Invalid shell or input\n"
# define ERR_OPEN_FAIL             "minishell: Error opening file\n"
# define ERR_TCGETATTR              "minishell: Failed to get terminal \
attributes\n"

//============================================================================//
//                            ERROR MESSAGES - BUILTINS                       //
//============================================================================//
# define ERR_CD_FAIL               "minishell: cd: %s: \
No such file or directory\n"
# define ERR_EXPORT_INVALID_IDENTIFIER "export: %s: not a valid identifier\n"
# define ERR_HOME_NOT_SET          "minishell: cd: HOME not set\n"
# define ERR_OLDPWD_NOT_SET        "minishell: cd: OLDPWD not set\n"
# define ERR_EXIT_NUM_REQ          "minishell: exit: %s: \
numeric argument required\n"
# define ERR_EXIT_TOO_MANY_ARGS    "minishell: exit: too many arguments\n"

//============================================================================//
//                            ERROR MESSAGES - INITIALIZATION                 //
//============================================================================//
# define ERR_ENV_DUP_FAIL          "minishell: Failed to duplicate \
environment\n"
# define ERR_GET_CWD_FAIL          "minishell: Failed to get current working \
directory\n"
# define ERR_SHELL_INIT_FAIL       "minishell: Failed to initialize shell\n"

//============================================================================//
//                            ERROR MESSAGES - MEMORY & SAFE FUNCTIONS        //
//============================================================================//
# define ERR_INVALID_ALLOC_SIZE    "minishell: Error: Invalid allocation \
size <= 0.\n"
# define ERR_MALLOC_FAIL           "minishell: fatal error: memory allocation \
failed\n"
# define ERR_STRDUP_FAIL           "minishell: Failed to duplicate string\n"
# define ERR_STRJOIN_FAIL          "minishell: String join operation failed\n"
# define ERR_SUBSTR_FAIL           "minishell: Substring creation failed\n"

//============================================================================//
//                            ERROR MESSAGES - PROMPT                         //
//============================================================================//
# define ERR_INVALID_PROMPT        "minishell: invalid prompt\n"

//============================================================================//
//                            ERROR MESSAGES - SIGNALS                        //
//============================================================================//
# define ERR_SIGNAL_SETUP_FAIL     "minishell: Failed to set up signal \
handlers\n"
# define ERR_SIGNAL_SETUP_INT      "minishell: Error setting up SIGINT \
handler\n"
# define ERR_SIGNAL_SETUP_QUIT     "minishell: Error setting up SIGQUIT \
handler\n"

//============================================================================//
//                            ERROR MESSAGES - SYNTAX                         //
//============================================================================//
# define ERR_SYNTAX_EOF_REDIR      "minishell: syntax error: redirection at \
end of input\n"
# define ERR_SYNTAX_UNCLOSED_QUOTE "minishell: syntax error: unmatched quotes \
detected\n"
# define ERR_SYNTAX_UNEXPECTED_TOKEN "minishell: syntax error near unexpected \
token `%s'\n"

//============================================================================//
//                            ERROR MESSAGES - REDIRECTIONS                   //
//============================================================================//
# define ERR_REDIR_NO_FILE         "minishell: %s: No such file or directory\n"

//============================================================================//
//                            ERROR MESSAGES - HEREDOC                        //
//============================================================================//
# define ERR_EOF_HEREDOC           "minishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n"
# define ERR_PIPE_FAIL             "minishell: error creating heredoc pipe\n"
# define ERR_TEMP_FILE             "minishell: could not create temp file\n"

//============================================================================//
//                            ERROR MESSAGES - TOKENIZATION                   //
//============================================================================//
# define ERR_COPY_TOKENS           "minishell: failed to copy tokens for child \
process\n"
# define ERR_NULL_TOKEN_VALUE      "minishell: Error: Null token value\n"
# define ERR_TOKEN_CREATION_FAIL   "minishell: Failed to create token\n"
# define ERR_TOKENIZATION_FAIL     "minishell: Failed to tokenize input\n"
# define ERR_WORD_COUNT_FAIL       "minishell: Failed to count words in input\n"

#endif
