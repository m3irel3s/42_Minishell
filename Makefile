# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 16:42:01 by jmeirele          #+#    #+#              #
#    Updated: 2025/01/23 16:54:43 by jmeirele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I. -I$(INC_DIR)
V_LEAKS     = --leak-check=full --show-leak-kinds=all
V_TRACKS    = --track-fds=yes --track-origins=yes --trace-children=yes
V_EXTRAS    = --suppressions=readline.supp
VGDB_ARGS	= --vgdb-error=0 $(V_LEAKS) $(V_TRACKS) $(V_EXTRAS)

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_DIR   = 42_Libft
SRC_DIR     = src
INC_DIR     = inc

SRC		=	$(SRC_DIR)/main.c

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(LIBFT) $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT)

$(LIBFT_DIR):
	git clone git@github.com:m3irel3s/42_Libft.git $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

gdb: all $(NAME)
	tmux split-window -h "gdb --tui --args --log-file=gdb.txt ./$(NAME)"
	tmux resize-pane -L 5
	make get_log

get_log:
	rm -f gdb.txt
	touch gdb.txt
	@if command -v lnav; then \
		lnav gdb.txt; \
	else \
		tail -f gdb.txt; \
	fi

val: $(NAME) $(SRC)
	valgrind $(VARGS) ./$(NAME)

test:
	./$(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re