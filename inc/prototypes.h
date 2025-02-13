/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/11 16:16:01 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//============================================================================//
//                                INTRODUCTION                                //
//============================================================================//
/* 000_intro.c */
void		ft_display_startup_banner(void);
int		ft_authors(void);

//============================================================================//
//                             INITIALIZATION                                 //
//============================================================================//
/* 200_inits/init.c */
void		ft_init_shell(t_shell *shell, char **envp);

//============================================================================//
//                               PROMPT HANDLING                              //
//============================================================================//
/* 300_prompt/prompt.c */
char		*ft_set_prompt(void);
char		*ft_get_current_directory(void);

//============================================================================//
//                              SIGNAL HANDLING                               //
//============================================================================//
/* 400_signals/signals.c */
void		ft_set_up_signals(void);
void		ft_handle_sigint(int sig);
void		ft_handle_sigquit(int sig);

//============================================================================//
//                                  PARSING                                   //
//============================================================================//
/* 500_parsing/parsing.c */
int		ft_parse_input(t_shell *shell);

//============================================================================//
//                              TOKENIZATION                                  //
//============================================================================//
/* 510_tokenization/tokens.c */
int		ft_tokenize(t_shell *shell);

/* 510_tokenization/process_export.c */
t_status	ft_process_export_assignment(t_shell *shell, char *word);

/* 510_tokenization/tokens_word_handling.c */
t_status	ft_handle_word(t_shell *shell, size_t *i, int *quoted_status);

//============================================================================//
//                              TOKEN UTILITIES                               //
//============================================================================//
/* 510_tokenization/tokens_utils.c */
void		ft_add_token_to_list(t_shell *shell, t_token *new_token);
t_token		*ft_create_token(char *value, t_token_type type);
t_token_type	ft_determine_token_type(char *value, size_t len);

/* 510_tokenization/tokens_utils_2.c */
int		ft_create_and_add_token(t_shell *shell, size_t start, size_t end,
								int quoted);


//============================================================================//
//                             SYNTAX VALIDATION                              //
//============================================================================//
/* 520_syntax_validation/syntax_validation.c */
t_status	ft_validate_syntax(t_token *token);

//============================================================================//
//                             VARIABLE EXPANSION                             //
//============================================================================//
/* 530_expansion/expand.c */
void		ft_expand_tokens(t_shell *shell);

//============================================================================//
//                               REDIRECTIONS                                 //
//============================================================================//
/* 540_redirects/redirects_setting.c */
void		ft_create_redirection_list(t_shell *shell);

/* 540_redirects/redirects_handling.c */
void		ft_handle_redirections(t_shell *shell);

//============================================================================//
//                                EXECUTION                                   //
//============================================================================//
/* 600_exec/exec.c */
void		ft_execute_input(t_shell *shell);

//============================================================================//
//                               BUILT-IN COMMANDS                            //
//============================================================================//
/* 610_builtins/echo.c */
void		ft_echo(t_shell *shell);

/* 610_builtins/cd.c */
void		ft_cd(t_shell *shell);

/* 610_builtins/env.c */
void		ft_env(t_shell *shell);

//============================================================================//
//                                  CLEANUP                                   //
//============================================================================//
/* 700_clean/clean.c */
void		ft_cleanup(t_shell *shell);

//============================================================================//
//                       ENVIRONMENT VARIABLE UTILITIES                       //
//============================================================================//
/* 800_utils/env_utils.c */
char		**ft_duplicate_env(char **envp);
char		*ft_get_env_value(char *var, char **env);
int		ft_get_var_index(char *var, char **env);
void		ft_set_env_value(char *var, char *value, char **env);

//============================================================================//
//                      CHARACTER AND COMMAND TYPE CHECKS                     //
//============================================================================//
/* 800_utils/check_type_functions.c */
int		ft_is_operator(char c);
int		ft_is_space(char c);
int		ft_is_quote(char c);
int		ft_is_command(char *value, size_t len);

//============================================================================//
//                          SAFE MEMORY AND IO OPERATIONS                     //
//============================================================================//
/* 800_utils/safe_functions.c */
void		*ft_safe_malloc(size_t size);
char		*ft_safe_readline(t_shell *shell);
char		*ft_strdup_safe(const char *s);

#endif
