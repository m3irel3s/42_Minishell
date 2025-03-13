/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/13 17:36:28 by meferraz         ###   ########.fr       */
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
char			*ft_get_git_branch(void);
char			*ft_shorten_path(char *path);

//============================================================================//
//                              SIGNAL HANDLING                               //
//============================================================================//
/* 400_signals/signals.c */
t_status		ft_set_up_signals(void);
t_status		ft_setup_sigint_ignore(struct sigaction *sa_ignore,
					struct sigaction *sa_old);

//============================================================================//
//                                  PARSING                                   //
//============================================================================//
/* 500_parsing/parsing.c */
t_status		ft_parse_input(t_shell *shell);

//============================================================================//
//                              TOKENIZATION                                  //
//============================================================================//
/* src/520_tokenization/tokens_count.c */
int				ft_count_words(char *input);

/* src/520_tokenization/tokens_split.c */
char			**ft_split_input(char *input);
int				ft_build_tokens(char *input, char **res, size_t *i, size_t *k);

/* src/520_tokenization/tokens_process.c */
t_status		ft_tokenize(t_shell *shell, char **split_input);

//============================================================================//
//                              TOKEN UTILITIES                               //
//============================================================================//
/* src/520_tokenization/tokens_utils.c */
t_token_type	ft_determine_token_type(char *og_value, char \
					*value, size_t len);

/* src/520_tokenization/tokens_utils_2.c */
t_status		ft_create_and_add_token(t_shell *shell, char *value,
					size_t len, int quoted);

/* src/520_tokenization/tokens_split_2.c */
int				ft_handle_t_operator(char *input, size_t *i, \
					char **res, size_t *k);
t_status		ft_process_word(char *input, size_t *i, char **res, size_t *k);

//============================================================================//
//                             ERROR HANDLING                                 //
//============================================================================//
/* 510_errors_handler/syntax_validation.c */
t_status		ft_validate_syntax(char *input);

/* 510_errors_handler/print_errors_exit_failure.c */
t_status		ft_print_error(char *error_msg);
t_status		ft_print_error_custom_status(char *error_msg, int exit_status);
t_status		ft_print_syntax_error(char *token);
t_status		ft_print_unmatched_quote_error(void);
t_status		ft_print_redirect_no_file_error(void);

/* 510_errors_handler/print_errors_misuse.c */
t_status		ft_print_error_misuse(char *error_msg);
t_status		ft_print_error_invalid_exit_arg(char *error_msg);

/* 510_errors_handler/print_errors_fatal_signal.c */
t_status		ft_print_error_fatal_signal(char *error_msg, int signal_number);

/* 510_errors_handler/print_errors_utils.c */
// char			*ft_format_error(char *err, const char *file);
t_status		ft_print_error_w_arg(char *error_msg, char *arg, int status);

/* 510_errors_handler/syntax_validation.c */
t_status		ft_skip_quotes(char *input, int *i, char quote);

/* 510_errors_handler/syntax_validation_2.c */
t_status		ft_validate_redirects(char *input);

//============================================================================//
//                             VARIABLE EXPANSION                             //
//============================================================================//
/* 530_expansion/expand.c */
char			*ft_expand(t_shell *shell, char *token);
char			*ft_process_char(char *expanded_value, char c);

/* 530_expansion/expand_handle_dollar.c */
char			*ft_handle_dollar(t_shell *shell, char *token, size_t *i);

//============================================================================//
//                                EXECUTION                                   //
//============================================================================//
/* 600_exec/exec.c */
void			ft_exec(t_shell *shell);
void			ft_execute_command(t_shell *shell, t_cmd_type cmd);
t_cmd_type		ft_get_cmd_type(char *cmd);

/* 600_exec/exec_utils.c */
t_status		ft_has_pipes(t_shell *shell);

/* 620_execve/execve.c */

/* 620_execve/execve_utils.c */
void			ft_execute_cmd(t_shell *shell, char *cmd);
char			*ft_get_path_to_execute(t_shell *shell, char *cmd);
char			*ft_add_cmd_to_path(char **arr, char *cmd);
char			**ft_create_arr_cmd(t_token *start_pos);
void			ft_cleanup_cmd_execution(char *path, char **arr);

/* 620_execve/path_errors.c */
void			ft_print_path_errors(char *cmd);
void			ft_check_is_dir(t_shell *shell, char *path, char **arr);

//============================================================================//
//                                  PIPES                                     //
//============================================================================//
/* 640_pipes/exec_pipes.c */
void			ft_handle_pipes(t_shell *shell);

/* 640_pipes/exec_pipes_utils.c */
t_pipe			*ft_allocate_and_create_pipes(t_token *tokens);
int				ft_count_pipes(t_token *tokens);
void			ft_advance_to_next_cmd(t_token **curr_cmd);

/* 640_pipes/exec_pipes_utils_2.c */
void			ft_cleanup_pipes(t_pipe *pipes, int num_pipes);
void			ft_close_child_pipes(t_pipe *pipes, int num_pipes);
void			ft_free_redirects(t_redirect *redirects);
void			ft_clean_and_exit(t_shell *sh);

/* 640_pipes/exec_pipes_child.c */
void			ft_execute_child(t_shell *sh, t_token *curr_cmd,
					int i, t_pipe *pipes);

//============================================================================//
//                         EXECUTION - REDIRECTIONS                           //
//============================================================================//
/* 630_redirects/exec_redirection.c */
t_status		ft_handle_redirections(t_shell *shell);
t_status		ft_apply_redirection(t_redirect *redirect);
/* 630_redirects/exec_redirection_utils.c */
void			ft_create_redirection_list(t_shell *shell);
/* 630_redirects/exec_redirection_utils_2.c */
void			ft_print_error_and_status(t_status *status);

//============================================================================//
//                         EXECUTION - HEREDOC                                //
//============================================================================//
/* 650_heredoc/heredoc_syntax.c */
t_status		ft_check_heredoc_syntax(t_token *token);
t_status		ft_handle_child_exit(int status, char *tempfile);
t_status		ft_handle_child_signal(int status, \
					char *tempfile);
t_status		ft_process_heredocs(t_shell *shell);

/* 650_heredoc/heredoc_input.c */
t_status		ft_handle_single_heredoc(t_shell *shell, t_token *current);

/* 650_heredoc/heredoc_input_2.c */
void			ft_read_heredoc_input(t_shell *shell, char *delimiter,
					int quoted, int fd);

/* 650_heredoc/heredoc_utils.c */
char			*ft_expanded_line(t_shell *shell, char *line);
void			ft_process_delimiter(t_token *current, t_token *delim,
					char *tempfile);

/* 650_heredoc/heredoc_tempfile.c */
t_status		ft_create_temp_file(t_shell *shell, char **tempfile);
void			ft_add_temp_file(t_shell *shell, char *tempfile);

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
void			ft_pwd(void);
/* 610_builtins/export.c */
void			ft_export(t_shell *shell);
void			ft_add_var_to_env(t_shell *shell, char *var,
					char *value, int sign);
/* 610_builtins/exit.c */
void			ft_exit(t_shell *shell);
void			ft_handle_eof(t_shell *shell);
/* 610_builtins/unset.c */
void			ft_unset(t_shell *shell);

/* 611_builtins_utils/export_print.c */
void			ft_print_export(t_shell *shell);
void			ft_output_export(char **export);
char			**ft_sort_export(char **export);

/* 611_builtins_utils/cd_and_pwd_utils.c*/
char			*ft_get_current_directory(void);

/* 611_builtins_utils/env_utils.c */
char			**ft_duplicate_env(char **envp);
int				ft_get_env_size(t_shell *shell);
void			ft_update_env(t_shell *shell);

//============================================================================//
//                       ENVIRONMENT VARIABLE UTILITIES                       //
//============================================================================//
/* 700_utils_other/variable_utils.c */
int				ft_get_str_length(char *str1, char *str2);
char			*ft_get_var_value(char *var, char **env);
int				ft_get_var_index(char *var, char **env);
char			*ft_get_var_name(char *str);
/* 700_utils_other/variable_utils_2.c */
char			*ft_update_var(char *var, char *value, int sign);
void			ft_update_or_add_var(char *var, char *value,
					t_shell *shell, int sign);
/* 611_builtins_utils/export_utils.c */
int				ft_check_var_chars(char *var);

//============================================================================//
//                      CHARACTER AND COMMAND TYPE CHECKS                     //
//============================================================================//
/* 700_utils_other/check_type_functions.c */
bool			ft_is_operator(char c);
bool			ft_is_double_operator(char *str);
bool			ft_is_space(char c);
bool			ft_is_quote(char c);
bool			ft_is_command(char *value, size_t len);

//============================================================================//
//                          SAFE MEMORY AND IO OPERATIONS                     //
//============================================================================//
/* 700_utils_other/safe_functions.c */
void			*ft_safe_calloc(size_t size);
char			*ft_safe_readline(t_shell *shell);
char			*ft_safe_strdup(char *s);
char			*ft_safe_strjoin(char *s1, char *s2, int free_s1);
char			*ft_safe_substr(char *s, int start, int len);

/* 700_utils_other/safe_functions_2.c */
char			*ft_safe_strndup(const char *s1, size_t n);

//============================================================================//
//                                  CLEANUP                                   //
//============================================================================//
/* 800_clean/clean.c */
void			ft_cleanup(t_shell *shell);
void			ft_cleanup_temp_files(t_shell *shell);
void			ft_cleanup_redirects(t_shell *shell);
void			ft_cleanup_tokens(t_shell *shell);
void			ft_cleanup_w_env(t_shell *shell);

/* 800_clean/free.c */
void			ft_free(void *ptr);
void			ft_free_token(t_token *token);
void			ft_free_tokens(t_token **tokens);
void			ft_free_arr(char **arr);
void			ft_close_fds(void);

#endif
