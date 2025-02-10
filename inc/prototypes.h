/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/10 14:38:28 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* 000_intro.c */
void			ft_display_startup_banner(void);
int				ft_authors(void);

/* 200_inits*/
/*init.c*/
void			ft_init_shell(t_shell *shell, char **envp);

/* 300_prompt*/
/*prompt.c*/
char			*ft_set_prompt(void);

/* 400_signals*/
/*signals.c*/
void			ft_set_up_signals(void);

/* 500_parsing*/
/*parsing.c*/
int				ft_parse_input(t_shell *shell);
/*tokens.c*/
int ft_tokenize(t_shell *shell);
/*tokens_utils.c*/
void			ft_add_token_to_list(t_shell *shell, t_token *new_token);
t_token			*ft_create_token(char *value, t_token_type type);
t_token_type	ft_determine_token_type(char *value, size_t len);
void			ft_set_command_type(t_token *token);
size_t			ft_get_operator_length(const char *input);
int				ft_create_and_add_token(t_shell *shell, size_t start, size_t end, t_token_type type);

/* 700_clean*/
/*clean.c*/
void			ft_cleanup(t_shell *shell);

/* 800_utils*/
/*check_type_functions.c*/
int				ft_is_operator(char c);
int				ft_is_space(char c);
int				ft_is_quote(char c);
int				ft_is_command(char *value, size_t len);
/*safe_funcitons.c */
void			*ft_safe_malloc(size_t size);
char			*ft_safe_readline(t_shell *shell);

#endif
