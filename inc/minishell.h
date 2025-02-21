/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:40:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/21 15:08:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../42_Libft/FT_Libft/inc/libft.h"
# include "../42_Libft/FT_Printf/inc/ft_printf.h"
# include "../42_Libft/Get_next_line/inc/get_next_line.h"

# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include "macros.h"
# include "types.h"
# include "prototypes.h"
# include "ansi.h"

#endif
