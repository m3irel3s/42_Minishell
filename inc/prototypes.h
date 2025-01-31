/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:45 by jmeirele          #+#    #+#             */
/*   Updated: 2025/01/31 14:01:56 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* 000_intro.c */
void	ft_display_startup_banner(void);
int		ft_authors(void);

/* 100_inits./init.c*/
void	ft_init_shell(t_shell *shell, char **envp);

/* 800_utils/safe_funcitons.c */
void	*ft_safe_malloc(size_t size);
void	*ft_safe_calloc(size_t count, size_t size);
char	*ft_safe_readline(t_shell *shell);

#endif