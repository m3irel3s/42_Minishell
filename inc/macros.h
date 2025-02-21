/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 14:26:21 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

//============================================================================//
//                              EXIT STATUS CODES                             //
//============================================================================//
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

//============================================================================//
//                           GENERAL ERROR MESSAGES                           //
//============================================================================//
# define ERR_INVALID_PARAMS \
	"minishell: Invalid parameters\n"

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
//                           PROMPT ERROR MESSAGES                            //
//============================================================================//
# define ERR_STRDUP_FAIL \
	"minishell: Failed to duplicate string\n"

//============================================================================//
//                           FILE ERROR MESSAGES                             //
//============================================================================//
# define ERR_OPEN_FAIL \
	"minishell: Error opening file\n"

//============================================================================//
//                           SAFE FUNCTIONS ERROR MESSAGES                           //
//============================================================================//
# define ERR_INVALID_ALLOC_SIZE \
    "minishell: Error: Invalid allocation size <= 0.\n"
# define ERR_MALLOC_FAIL \
    "minishell: fatal error: memory allocation failed\n"
# define ERR_INVALID_PROMPT \
	"minishell: invalid prompt\n"
# define ERR_STRJOIN_FAIL "minishell: String join operation failed\n"

//============================================================================//
//                           SIGNAL ERROR MESSAGES                            //
//============================================================================//
# define ERR_SIGNAL_SETUP_INT \
	"minishell: Error setting up SIGINT handler\n"
# define ERR_SIGNAL_SETUP_QUIT \
	"minishell: Error setting up SIGQUIT handler\n"
# define ERR_SIGNAL_SETUP_FAIL \
	"minishell: Failed to set up signal handlers\n"

#endif

