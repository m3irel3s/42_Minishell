# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 16:57:53 by meferraz          #+#    #+#              #
#    Updated: 2025/03/11 16:27:57 by jmeirele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                              MINISHELL PROJECT                               #
#==============================================================================#

## Main target name ##
NAME        = minishell

#------------------------------------------------------------------------------#
#                                COLORS & STYLES                               #
#------------------------------------------------------------------------------#

## ANSI color codes for prettier output ##
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

## Text style codes ##
BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m

## Emojis for visual feedback ##
CHECK = ✓
CLEAN = 🧹
BUILD = 🔨
ROCKET = 🚀
BOOK = 📚
SPARKLES = ✨

#------------------------------------------------------------------------------#
#                            	  NAMES AND PATHS                              #
#------------------------------------------------------------------------------#

## Directory structure ##
BUILD_PATH = .build
SRC_PATH = src
INC_PATH = inc

## Header files ##
HEADERS = ${addprefix ${INC_PATH}/, \
	ansi.h \
	minishell.h \
	macros.h \
	prototypes.h \
	types.h}

## Source files for main program ##

SRCS = \
       ${SRC_PATH}/000_intro.c \
       ${SRC_PATH}/100_main.c \
       ${SRC_PATH}/200_inits/init.c \
       ${SRC_PATH}/300_prompt/prompt.c \
       ${SRC_PATH}/300_prompt/prompt_utils.c \
       ${SRC_PATH}/400_signals/signals.c \
       ${SRC_PATH}/500_parsing/parsing.c \
       ${SRC_PATH}/510_errors_handler/syntax_validation.c \
       ${SRC_PATH}/510_errors_handler/syntax_validation_2.c \
       ${SRC_PATH}/510_errors_handler/print_errors_exit_failure.c \
       ${SRC_PATH}/510_errors_handler/print_errors_misuse.c \
       ${SRC_PATH}/510_errors_handler/print_errors_fatal_signal.c \
       ${SRC_PATH}/510_errors_handler/print_errors_utils.c \
       ${SRC_PATH}/520_tokenization/tokens_process.c \
       ${SRC_PATH}/520_tokenization/tokens_utils.c \
       ${SRC_PATH}/520_tokenization/tokens_utils_2.c \
       ${SRC_PATH}/520_tokenization/tokens_count.c \
       ${SRC_PATH}/520_tokenization/tokens_split.c \
       ${SRC_PATH}/520_tokenization/tokens_split_2.c \
       ${SRC_PATH}/530_expansion/expand.c \
       ${SRC_PATH}/530_expansion/expand_handle_dollar.c \
       ${SRC_PATH}/600_exec/exec.c \
       ${SRC_PATH}/600_exec/exec_utils.c \
       ${SRC_PATH}/610_builtins/cd.c \
       ${SRC_PATH}/610_builtins/echo.c \
       ${SRC_PATH}/610_builtins/env.c \
       ${SRC_PATH}/610_builtins/pwd.c \
       ${SRC_PATH}/610_builtins/export.c \
       ${SRC_PATH}/610_builtins/unset.c \
       ${SRC_PATH}/610_builtins/exit.c \
       ${SRC_PATH}/611_builtins_utils/env_utils.c \
       ${SRC_PATH}/611_builtins_utils/export_utils.c \
       ${SRC_PATH}/611_builtins_utils/export_print.c \
       ${SRC_PATH}/611_builtins_utils/cd_and_pwd_utils.c \
       ${SRC_PATH}/620_execve/execve.c \
       ${SRC_PATH}/620_execve/execve_utils.c \
       ${SRC_PATH}/620_execve/path_errors.c \
       ${SRC_PATH}/630_redirects/exec_redirection.c \
       ${SRC_PATH}/630_redirects/exec_redirection_utils.c \
       ${SRC_PATH}/640_pipes/exec_pipes_child.c \
       ${SRC_PATH}/640_pipes/exec_pipes_utils.c \
       ${SRC_PATH}/640_pipes/exec_pipes.c \
       ${SRC_PATH}/640_pipes/exec_pipes_utils_2.c \
       ${SRC_PATH}/650_heredoc/heredoc_syntax.c \
       ${SRC_PATH}/650_heredoc/heredoc_utils.c \
       ${SRC_PATH}/650_heredoc/heredoc_input.c \
       ${SRC_PATH}/650_heredoc/heredoc_input_2.c \
       ${SRC_PATH}/650_heredoc/heredoc_tempfile.c \
       ${SRC_PATH}/700_utils_other/variable_utils.c \
       ${SRC_PATH}/700_utils_other/variable_utils_2.c \
       ${SRC_PATH}/700_utils_other/check_type_functions.c \
       ${SRC_PATH}/700_utils_other/safe_functions.c \
       ${SRC_PATH}/700_utils_other/safe_functions_2.c \
       ${SRC_PATH}/800_clean/clean.c \
       ${SRC_PATH}/800_clean/free.c

# Object files derived from source files
# OBJS = ${addprefix ${BUILD_PATH}/, ${notdir ${SRCS:.c=.o}}}
OBJS = ${SRCS:${SRC_PATH}/%.c=${BUILD_PATH}/%.o}

## Libft ##
LIBFT_PATH = 42_Libft
LIBFT_ARC = ${LIBFT_PATH}/libft.a

#------------------------------------------------------------------------------#
#                            	   FLAGS & COMMANDS                            #
#------------------------------------------------------------------------------#

## Core ##
CC				= cc
CCFLAGS			= -Wall -Wextra -Werror -g
SANITIZE		= -fsanitize=address
RM				= rm -fr
MKDIR_P			= mkdir -p
INC				= -I ${INC_PATH}  -I$(READLINE_PATH)/include
MAKE			= make --no-print-directory -C
MAKE_RE			= make --no-print-directory all

## Libft ##
LDFLAGS			= -L${LIBFT_PATH} -lft

## Valgrind ##
# --trace-children=yes
V_LEAKS			= --leak-check=full --tool=memcheck --show-leak-kinds=all
V_TRACKS		= --track-origins=yes --track-fds=yes
V_EXTRAS		= --suppressions=readline.supp
VGDB_ARGS		= --vgdb-error=0 $(V_LEAKS) $(V_TRACKS) $(V_EXTRAS)
V_ARGS			= $(V_LEAKS) $(V_TRACKS) $(V_EXTRAS)

## Readline ##
READL_FLAG		= -L$(READLINE_PATH)/lib -I$(READLINE_PATH)/include -lreadline -lncurses
READLINE_PATH	= /opt/homebrew/opt/readline

#------------------------------------------------------------------------------#
#                                    RULES                                     #
#------------------------------------------------------------------------------#

##  Compilation Rules for minishell  ##

all: deps ${NAME}

${NAME}: ${BUILD_PATH} ${OBJS} ${LIBFT_ARC}
	@printf "${CYAN}${DIM}Compiling source files for minishell...${RESET}\n"
	@${CC} ${CCFLAGS} ${OBJS} -o ${NAME} ${LDFLAGS} ${READL_FLAG}
	@printf "${GREEN}${BOLD}${CHECK} minishell executable compiled successfully!${RESET}\n"

${BUILD_PATH}:
	@printf "\n${BLUE}${BOLD}Creating build directory...${RESET}\n"
	@${MKDIR_P} ${BUILD_PATH}
	@printf "${GREEN}${BOLD}${CHECK} Build directory created successfully!${RESET}\n"

${BUILD_PATH}/%.o: ${SRC_PATH}/%.c ${HEADERS} | ${BUILD_PATH}
	@printf "${CYAN}${DIM}Compiling: ${WHITE}%-30s${RESET}\r" ${notdir $<}
	@${MKDIR_P} $(dir $@)  # Ensure subdirectories in .build exist
	@${CC} ${CCFLAGS} ${INC} -c $< -o $@

${LIBFT_ARC}: deps
	@printf "${CYAN}${BOLD}${DIM} Compiling Libft..${RESET}\n"
	@${MAKE} ${LIBFT_PATH}
	@printf "${BLUE}${BOLD}${BUILD} ${WHITE}${LIBFT_ARC}${GREEN} compiled! ${RESET}\n"

deps:
	@printf "${GREEN}${BOLD}${ROCKET} All dependencies are up to date!${RESET}\n"
	@if test ! -d "${LIBFT_PATH}"; then make get_libft; \
		else printf "${GREEN}${BOLD}${ROCKET} ${WHITE}${LIBFT_ARC}${GREEN} folder found!${RESET}\n"; fi

get_libft:
	@printf "${CYAN}${BOLD}${BOOK} Getting Libft..${RESET}\n"
	@git clone https://github.com/m3irel3s/42_Libft ${LIBFT_PATH}
	@git pull
	@printf "${GREEN}${BOLD}${ROCKET} ${WHITE}${LIBFT_ARC}${GREEN} successfully downloaded!${RESET}\n"

##  Testing Rules  ##

val: deps $(NAME)
	valgrind $(V_ARGS) ./$(NAME)

vgdb: deps $(NAME)
	valgrind --vgdb-error=0 $(V_ARGS) ./$(NAME)

##  Debugging Rules ##

gdb: all $(NAME)
	gdb -tui -x .gdbinit ./$(NAME)

test: all $(NAME)
	./$(NAME)

##  Cleaning Rules  ##

clean:                       # Clean up object files and temporary build files
	@printf "\n${YELLOW}${BOLD}${CLEAN} Cleaning object files...${RESET}\n"
	@${RM} ${OBJS}
	@printf "${GREEN}${BOLD}${CHECK} Object files cleaned!${RESET}\n"

fclean: clean               # Fully clean up by removing executables and build directories
	@printf "${YELLOW}${BOLD}${CLEAN} Removing executable and build files...${RESET}\n"
	@${RM} ${NAME}
	@${RM} -r ${BUILD_PATH}
	@${RM} ${LIBFT_PATH}
	@printf "${GREEN}${BOLD}${CHECK} All files cleaned!${RESET}\n"

re: fclean all          # Rebuild everything from scratch
	@printf "${YELLOW}${BOLD}${BUILD} Rebuilding everything...${RESET}\n"
	@${MAKE_RE}

##  Norms Rules  ##

norm:
	@printf "\n${BLUE}${BOLD}${TEST} Checking Norminette...${RESET}\n"
	@norminette_files=$$(find . -name "*.c" -o -name "*.h"); \
	if [ -n "$$norminette_files" ]; then \
		norminette_output=$$(norminette $$norminette_files); \
		error_count=0; \
		echo "$$norminette_output" | while IFS= read -r line; do \
			if echo "$$line" | grep -q "Error:"; then \
				printf "${RED}${BOLD}$$line${RESET}\n"; \
				error_count=$$((error_count + 1)); \
			elif echo "$$line" | grep -q ": OK!"; then \
				printf "${GREEN}$$line${RESET}\n"; \
			else \
				printf "  ${WHITE}$$line${RESET}\n"; \
			fi; \
		done; \
		if [ $$error_count -gt 0 ]; then \
			printf "\n${RED}${BOLD}❌ Found $$error_count norminette error(s).${RESET}\n"; \
		else \
			printf "\n${GREEN}${BOLD}✓ No norminette errors found!${RESET}\n"; \
		fi; \
	else \
		printf "${YELLOW}${BOLD}⚠️ No .c or .h files found to check!${RESET}\n"; \
	fi
	@printf "${BLUE}${BOLD}${TEST} Norminette check completed!${RESET}\n"

##   Check for external functions  ##
check_external_functions: all               # Check norms for mandatory sources
	@printf "\n${BLUE}${BOLD}${TEST} Checking External Functions...${RESET}\n"
	nm ./${NAME} | grep "U" | grep -v "__"
	@printf "${GREEN}${BOLD}${CHECK} External functions check completed!${RESET}\n"

.PHONY: all clean fclean re norm check_external_functions
