/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/04 10:54:07 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* 000_intro.c */
void	ft_display_startup_banner(void);
int		ft_authors(void);

/* 200_inits*/
/*init.c*/
void	ft_init_shell(t_shell *shell, char **envp);

/* 300_prompt*/
/*prompt.c*/
char	*ft_set_prompt(void);

/* 400_signals*/
/*signals.c*/
void	ft_set_up_signals(void);

/* 500_parsing*/
/*parsing.c*/
int		ft_parse_input(t_shell *shell);
/*tokens.c*/
int		ft_tokenize(t_shell *shell);
/*tokens_utils.c*/
t_token_type	t_determine_token_type(char *value);
t_token			*ft_create_token(char *value, t_token_type type);
void			ft_add_token_to_list(t_shell *shell, t_token *new_token);

/* 700_clean*/
/*clean.c*/
void	ft_cleanup(t_shell *shell);

/* 800_utils*/
/*char_type_functions.c*/
int		ft_is_operator(char c);
int		ft_is_space(char c);
/*safe_funcitons.c */
void	*ft_safe_malloc(size_t size);
void	*ft_safe_calloc(size_t count, size_t size);
char	*ft_safe_readline(t_shell *shell);

#endif
