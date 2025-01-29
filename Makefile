# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 16:57:53 by meferraz          #+#    #+#              #
#    Updated: 2025/01/29 11:56:31 by jmeirele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                              MINISHELL PROJECT                               #
#==============================================================================#

# Main target name
NAME        = minishell

#------------------------------------------------------------------------------#
#                                COLORS & STYLES                               #
#------------------------------------------------------------------------------#

# ANSI color codes for prettier output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Text style codes
BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m

# Emojis for visual feedback
CHECK = ✓
CLEAN = 🧹
BUILD = 🔨
ROCKET = 🚀
BOOK = 📚
SPARKLES = ✨

#------------------------------------------------------------------------------#
#                            	  NAMES AND PATHS                              #
#------------------------------------------------------------------------------#

# Directory structure
BUILD_PATH = .build
SRC_PATH = src
INC_PATH = inc

# Header files
HEADERS = ${addprefix ${INC_PATH}/, \
	minishell.h \
	macros.h \
	prototypes.h \
	types.h}

# Source files for main program
SRCS = ${addprefix ${SRC_PATH}/, \
	main.c}

# Object files derived from source files
OBJS = ${addprefix ${BUILD_PATH}/, ${notdir ${SRCS:.c=.o}}}

LIBFT_PATH = 42_Libft
LIBFT_ARC = ${LIBFT_PATH}/libft.a

#------------------------------------------------------------------------------#
#                            	   FLAGS & COMMANDS                            #
#------------------------------------------------------------------------------#


CC          = cc
CCFLAGS     = -Wall -Wextra -Werror -g
V_LEAKS     = --leak-check=full --show-leak-kinds=all
V_TRACKS    = --track-fds=yes --track-origins=yes --trace-children=yes
V_EXTRAS    = --suppressions=readline.supp
VGDB_ARGS	= --vgdb-error=0 $(V_LEAKS) $(V_TRACKS) $(V_EXTRAS)
V_ARGS      = $(V_LEAKS) $(V_TRACKS) $(V_EXTRAS)
READL_FLAG  = -lreadline
RM          = rm -fr                       # Command to remove files/directories forcefully
MKDIR_P     = mkdir -p                # Command to create directories (with parent)
INC         = -I ${INC_PATH}              # Include path for header files
LDFLAGS     = -L${LIBFT_PATH} -lft
MAKE        = make --no-print-directory -C
MAKE_EXTRA  = make extra --no-print-directory -C

#------------------------------------------------------------------------------#
#                                    RULES                                     #
#------------------------------------------------------------------------------#

##  Compilation Rules for minishell  ##

all: deps ${NAME}

${NAME}: ${BUILD_PATH} ${OBJS} ${LIBFT_ARC}
	@printf "${CYAN}${DIM}Compiling source files for minishell...${RESET}\n"
	@${CC} ${CCFLAGS} ${OBJS} -o ${NAME} ${LDFLAGS}
	@printf "${GREEN}${BOLD}${CHECK} minishell executable compiled successfully!${RESET}\n"

${BUILD_PATH}:
	@printf "\n${BLUE}${BOLD}Creating build directory...${RESET}\n"
	@${MKDIR_P} ${BUILD_PATH}
	@printf "${GREEN}${BOLD}${CHECK} Build directory created successfully!${RESET}\n"

${BUILD_PATH}/%.o: ${SRC_PATH}/%.c ${HEADERS} | ${BUILD_PATH}
	@printf "${CYAN}${DIM}Compiling: ${WHITE}%-30s${RESET}\r" ${notdir $<}
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
	@${MAKE} all

##  Norms Rules  ##

norm:                # Check norms for mandatory sources
	@printf "\n${BLUE}${BOLD}${TEST} Checking Norminette...${RESET}\n"
	@norminette_output=$$(norminette *.c *.h | grep -v "OK!" || true); \
	if [ -z "$$norminette_output" ]; then \
		printf "${GREEN}${BOLD}${CHECK} No norminette errors found!${RESET}\n"; \
	else \
		printf "$$norminette_output\n"; \
		printf "${RED}${BOLD}❌ Norminette errors found.${RESET}\n"; \
	fi
	@printf "${GREEN}${BOLD}${CHECK} Norminette check completed!${RESET}\n"

##   Check for external functions  ##
check_external_functions: all               # Check norms for mandatory sources 
	@printf "\n${BLUE}${BOLD}${TEST} Checking External Functions...${RESET}\n"
	nm ./${NAME} | grep "U" | grep -v "__"
	@printf "${GREEN}${BOLD}${CHECK} External functions check completed!${RESET}\n"

.PHONY: all clean fclean re norm check_external_functions