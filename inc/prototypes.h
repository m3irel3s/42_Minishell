/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 14:14:40 by jmeirele         ###   ########.fr       */
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
t_status		ft_init_shell(t_shell *shell, char **envp);

//============================================================================//
//                               PROMPT HANDLING                              //
//============================================================================//
/* 300_prompt/prompt.c */
char			*ft_set_prompt(t_shell *shell);

/* 300_prompt/prompt_utils.c */
char			*ft_get_git_branch(t_shell *shell);
char			*ft_shorten_path(t_shell *shell, char *path);
char			*ft_handle_error(t_shell *shell, char *error_msg);

//============================================================================//
//                              SIGNAL HANDLING                               //
//============================================================================//
/* 400_signals/signals.c */
t_status		ft_set_up_signals(void);

//============================================================================//
//                                  PARSING                                   //
//============================================================================//
/* 500_parsing/parsing.c */
t_status		ft_parse_input(t_shell *shell);

//============================================================================//
//                              TOKENIZATION                                  //
//============================================================================//
/* 510_tokenization/tokens.c */
t_status		ft_tokenize(t_shell *shell);

//============================================================================//
//                              TOKEN UTILITIES                               //
//============================================================================//
/* 510_tokenization/tokens_utils.c */
t_token_type	ft_determine_token_type(t_shell *shell, char *value,
					size_t len);
/* 510_tokenization/tokens_utils_2.c */
int				ft_create_and_add_token(t_shell *shell, size_t start,
					size_t end, int quoted);

//============================================================================//
//                       TOKENIZATION - HELPERS FUNCTIONS                     //
//============================================================================//
/* 510_tokenization/tokens_helpers.c */
int				ft_is_export_command(t_shell *shell, size_t i);
t_status		ft_create_export_token(t_shell *shell, size_t *i,
					int *is_export);

//============================================================================//
//                  TOKENIZATION - OPERATORS AND EXPORT ARGUMENTS             //
//============================================================================//
/* 510_tokenization/tokens_handlers.c */
t_status		ft_handle_operator(t_shell *shell, size_t *i, int *is_export);
/* 510_tokenization/tokens_handlers_2.c */
t_status		ft_handle_export_arg(t_shell *shell, size_t *i);
void			ft_reset_quote_info(t_quote_info *quote_info);

//============================================================================//
//                       TOKENIZATION - WORD PROCESSING                       //
//============================================================================//
/* 510_tokenization/tokens_word_handlers.c */
t_status		ft_handle_word(t_shell *shell, size_t *i);

//============================================================================//
//                             ERROR HANDLING                                 //
//============================================================================//
/* 520_errors_handler/syntax_validation.c */
t_status		ft_validate_syntax(t_shell *shell, t_token *token);

/* 520_errors_handler/print_errors_exit_failure.c */
t_status		ft_print_error(t_shell *shell, char *error_msg);
t_status		ft_print_error_custom_status(t_shell *shell, char *error_msg,
					int exit_status);
t_status		ft_print_syntax_error(t_shell *shell, char *token);
t_status		ft_print_unmatched_quote_error(t_shell *shell);
t_status		ft_print_redirect_no_file_error(t_shell *shell);

/* 520_errors_handler/print_errors_heredoc.c */
t_status		ft_print_heredoc_delim_error(t_shell *shell);

/* 520_errors_handler/print_errors_command_not_found.c */
t_status		ft_print_command_not_found_error(t_shell *shell, char *cmd);

/* 520_errors_handler/print_errors_misuse.c */
t_status		ft_print_error_misuse(t_shell *shell, char *error_msg);
t_status		ft_print_error_invalid_exit_arg(t_shell *shell,
					char *error_msg);

/* 520_errors_handler/print_errors_fatal_signal.c */
t_status		ft_print_error_fatal_signal(t_shell *shell, char *error_msg,
					int signal_number);

//============================================================================//
//                             VARIABLE EXPANSION                             //
//============================================================================//
/* 530_expansion/expand.c */
t_status		ft_expand(t_shell *shell);
char			*ft_process_char(t_shell *shell, char *expanded_value, char c);
/* 530_expansion/expand_handle_dollar.c */
char			*ft_handle_dollar(t_shell *shell, char *token, size_t *i);

//============================================================================//
//                                EXECUTION                                   //
//============================================================================//
/* 600_exec/exec.c */
void			ft_exec(t_shell *shell);
t_cmd_type		ft_get_cmd_type(char *cmd);
void			ft_handle_exec(t_shell *shell, int cmd);
void			ft_execute_command(t_shell *shell, int cmd);

/* 620_execve/exec_execve.c */
void			ft_execute_cmd(t_shell *shell, char *cmd);
char			*ft_get_path_to_execute(t_shell *shell, char *cmd);
char			*ft_add_cmd_to_path(t_shell *shell, char **arr, char *cmd);
char			**ft_create_arr_cmd(t_token *start_pos);

//============================================================================//
//                                  PIPES                                     //
//============================================================================//
/* 600_exec/exec_pipes.c */
void			ft_handle_pipes(t_shell *shell);
/* 600_exec/exec_utils.c */
int				ft_has_pipes(t_shell *shell);

//============================================================================//
//                         EXECUTION - REDIRECTIONS                           //
//============================================================================//
/* 630_redirects/exec_redirection.c */
void			ft_handle_redirections(t_shell *shell);
/* 630_redirects/exec_redirection_utils.c */
void			ft_create_redirection_list(t_shell *shell);
/* 630_redirects/exec_heredoc.c */
void			ft_redirect_heredoc(t_shell *shell, t_redirect *redirect);

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
/* 610_builtins/exit.c */
void			ft_exit(t_shell *shell);
void			ft_handle_eof(t_shell *shell);
/* 610_builtins/unset.c */
void			ft_unset(t_shell *shell);

/* 611_builtins_utils/export_print.c */
void			ft_print_export(t_shell *shell);
void			ft_output_export(char **export);
char			**ft_sort_export(char **export);

/*611_builtins_utils/cd_and_pwd_utils.c*/
char			*ft_get_current_directory(t_shell *shell);

/* 611_builtins_utils/env_utils.c */
char			**ft_duplicate_env(char **envp);
int				ft_get_env_size(t_shell *shell);

//============================================================================//
//                       ENVIRONMENT VARIABLE UTILITIES                       //
//============================================================================//

/* 700_utils_other/variable_utils.c */
int				ft_get_str_length(char *str1, char *str2);
char			*ft_get_var_value(char *var, char **env);
int				ft_get_var_index(char *var, char **env);
char			*ft_get_var_name(char *str);
/* 700_utils_other/variable_utils_2.c */
char			*ft_update_var(char *var, char *value);
void			ft_update_or_add_var(char *var, char *value, t_shell *shell);
/* 611_builtins_utils/export_utils.c */
int				ft_check_var_chars(char *var);

//============================================================================//
//                      CHARACTER AND COMMAND TYPE CHECKS                     //
//============================================================================//
/* 700_utils_other/check_type_functions.c */
int				ft_is_operator(char c);
int				ft_is_double_operator(char *str);
int				ft_is_space(char c);
int				ft_is_quote(char c);
int				ft_is_command(char *value, size_t len);

//============================================================================//
//                          SAFE MEMORY AND IO OPERATIONS                     //
//============================================================================//
/* 700_utils_other/safe_functions.c */
void			*ft_safe_malloc(size_t size);
char			*ft_safe_readline(t_shell *shell);
char			*ft_safe_strdup(char *s);
char			*ft_safe_strjoin(t_shell *shell, char *s1, char *s2,
	int free_s1);

//============================================================================//
//                                  CLEANUP                                   //
//============================================================================//
/* 800_clean/clean.c */
void			ft_cleanup(t_shell *shell);
/* 800_clean/free.c */
void			ft_free(void *ptr);
void			ft_free_token(t_token *token);
void			ft_free_arr(char **arr);

#endif
