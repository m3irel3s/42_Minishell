/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/18 09:25:18 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//============================================================================//
//                                INTRODUCTION                                //
//============================================================================//
/* 000_intro.c */
void			ft_display_startup_banner(void);
int				ft_authors(void);

//============================================================================//
//                             INITIALIZATION                                 //
//============================================================================//
/* 200_inits/init.c */
void			ft_init_shell(t_shell *shell, char **envp);

//============================================================================//
//                               PROMPT HANDLING                              //
//============================================================================//
/* 300_prompt/prompt.c */
char			*ft_set_prompt(void);
char			*ft_get_current_directory(void);

//============================================================================//
//                              SIGNAL HANDLING                               //
//============================================================================//
/* 400_signals/signals.c */
void			ft_set_up_signals(void);
void			ft_handle_sigint(int sig);
void			ft_handle_sigquit(int sig);

//============================================================================//
//                                  PARSING                                   //
//============================================================================//
/* 500_parsing/parsing.c */
int				ft_parse_input(t_shell *shell);

//============================================================================//
//                              TOKENIZATION                                  //
//============================================================================//
/* 510_tokenization/tokens.c */
t_status		ft_tokenize(t_shell *shell);

//============================================================================//
//                              TOKEN UTILITIES                               //
//============================================================================//
/* 510_tokenization/tokens_utils.c */
t_token_type	ft_determine_token_type(char *value, size_t len);

/* 510_tokenization/tokens_utils_2.c */
int				ft_create_and_add_token(t_shell *shell, size_t start, size_t end,
								int quoted);
t_token			*ft_init_new_token(t_shell *shell, size_t start, size_t end,
								int quoted);
void			ft_add_token_to_shell(t_shell *shell, t_token *new_token);

//============================================================================//
//                       TOKENIZATION - HELPERS FUNCTIONS                     //
//============================================================================//
/* 510_tokenization/tokens_helpers.c */
int				ft_is_export_command(t_shell *shell, size_t i);
t_status		ft_create_export_token(t_shell *shell, size_t *i, int *is_export);

//============================================================================//
//                  TOKENIZATION - OPERATORS AND EXPORT ARGUMENTS             //
//============================================================================//
/* 510_tokenization/tokens_handlers.c */
t_status		ft_handle_operator(t_shell *shell, size_t *i, int *is_export);
t_status		ft_handle_export_arg(t_shell *shell, size_t *i);

//============================================================================//
//                       TOKENIZATION - WORD PROCESSING                       //
//============================================================================//
/* 510_tokenization/tokens_word_handlers.c */
t_status		ft_handle_word(t_shell *shell, size_t *i);

//============================================================================//
//                             SYNTAX VALIDATION                              //
//============================================================================//
/* 520_syntax_validation/syntax_validation.c */
t_status		ft_validate_syntax(t_token *token);
t_status		ft_print_unmatched_quote_error(void);
t_status		ft_print_syntax_error(char *token);
t_status		ft_print_redirect_no_file_error(void);
t_status		ft_print_heredoc_delim_error(void);
t_status		ft_print_command_not_found_error(char *cmd);

//============================================================================//
//                             VARIABLE EXPANSION                             //
//============================================================================//
/* 530_expansion/expand.c */
t_status		ft_expand(t_shell *shell);

/* 530_expansion/expand_handle_dollar.c */
char			*ft_handle_dollar(t_shell *shell, char *token, size_t *i);

//============================================================================//
//                               REDIRECTIONS                                 //
//============================================================================//
/* 540_redirects/redirects_setting.c */
void			ft_create_redirection_list(t_shell *shell);

/* 540_redirects/redirects_handling.c */
void			ft_handle_redirections(t_shell *shell);

//============================================================================//
//                                EXECUTION                                   //
//============================================================================//
/* 600_exec/exec.c */
void			ft_execute_input(t_shell *shell);
void			ft_handle_exec(t_shell *shell);
t_cmd_type		ft_get_cmd_type(char *cmd);



//============================================================================//
//                               BUILT-IN COMMANDS                            //
//============================================================================//
/* 610_builtins/echo.c */
void			ft_echo(t_shell *shell);

/* 610_builtins/cd.c */
void			ft_cd(t_shell *shell);


/* 610_builtins/env.c */
void			ft_env(t_shell *shell);

/* 610_builtins/pwd.c */
void			ft_pwd(t_shell *shell);

/* 610_builtins/export.c */
void			ft_export(t_shell *shell);
void			ft_add_var_to_env(t_shell *shell, char *var, char *value);

/* 610_builtins/export_print.c */
void			ft_print_export(char **export);
char			**ft_sort_export(char **export);

/* 610_builtins/exit.c */
void			ft_exit(t_shell *shell);

/* 610_builtins/unset.c */
void			ft_unset(t_shell *shell);


//============================================================================//
//                                  CLEANUP                                   //
//============================================================================//
/* 700_clean/clean.c */
void			ft_cleanup(t_shell *shell);
void			ft_free(void *ptr);
void			ft_free_token(t_token *token);
void			ft_free_arr(char **arr);

//============================================================================//
//                       ENVIRONMENT VARIABLE UTILITIES                       //
//============================================================================//

/* 800_utils*/
/* env_utils.c */
char			**ft_duplicate_env(char **envp);
int				ft_get_env_size(t_shell *shell);

/* variable_utils.c */
int				ft_get_str_length(char *str1, char *str2);
char			*ft_get_var_value(char *var, char **env);
int				ft_get_var_index(char *var, char **env);
char			*ft_get_var_name(char *str);

/* variable_utils_2.c */
char			*ft_update_var(char *var, char *value);
void			ft_update_or_add_var(char *var, char *value, t_shell *shell);

/* export_utils.c */
int				ft_check_var_chars(char *var);


//============================================================================//
//                      CHARACTER AND COMMAND TYPE CHECKS                     //
//============================================================================//
/* 800_utils/check_type_functions.c */
int				ft_is_operator(char c);
int				ft_is_double_operator(const char *str);
int				ft_is_space(char c);
int				ft_is_quote(char c);
int				ft_is_command(char *value, size_t len);

//============================================================================//
//                          SAFE MEMORY AND IO OPERATIONS                     //
//============================================================================//
/* 800_utils/safe_functions.c */
void			*ft_safe_malloc(size_t size);
char			*ft_safe_readline(t_shell *shell);
char			*ft_strdup_safe(const char *s);

#endif
