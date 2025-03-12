# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 16:57:53 by meferraz          #+#    #+#              #
#    Updated: 2025/03/12 10:59:43 by jmeirele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                              MINISHELL PROJECT                               #
#==============================================================================#

NAME        = minishell
OS          = $(shell uname -s)

#------------------------------------------------------------------------------#
#                                COLORS & STYLES                               #
#------------------------------------------------------------------------------#

RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
CYAN        = \033[0;36m
WHITE       = \033[0;37m
RESET       = \033[0m
BOLD        = \033[1m
DIM         = \033[2m
CHECK       = ✔️
CROSS       = ❌
CLEAN       = 🧹
BUILD       = 🔨
ROCKET      = 🚀
BOOK        = 📚

#------------------------------------------------------------------------------#
#                             ALLOWED FUNCTIONS                                #
#------------------------------------------------------------------------------#

ALLOWED_FUNCS = readline rl_clear_history rl_on_new_line rl_replace_line \
				rl_redisplay add_history printf malloc free write access \
				open read close fork wait waitpid wait3 wait4 signal \
				sigaction sigemptyset sigaddset kill exit getcwd chdir \
				stat lstat fstat unlink execve dup dup2 pipe opendir \
				readdir closedir strerror perror isatty ttyname ttyslot \
				ioctl getenv tcsetattr tcgetattr tgetent tgetflag tgetnum \
				tgetstr tgoto tputs

#------------------------------------------------------------------------------#
#                             NAMES AND PATHS                                  #
#------------------------------------------------------------------------------#

BUILD_PATH  = .build
SRC_PATH    = src
INC_PATH    = inc
LIBFT_PATH  = 42_Libft
LIBFT_ARC   = $(LIBFT_PATH)/libft.a

HEADERS     = $(addprefix $(INC_PATH)/, ansi.h minishell.h macros.h prototypes.h types.h)

SRCS        = $(SRC_PATH)/000_intro.c \
			$(SRC_PATH)/100_main.c \
			$(SRC_PATH)/200_inits/init.c \
			$(SRC_PATH)/300_prompt/prompt.c \
			$(SRC_PATH)/300_prompt/prompt_utils.c \
			$(SRC_PATH)/400_signals/signals.c \
			$(SRC_PATH)/500_parsing/parsing.c \
			$(SRC_PATH)/510_errors_handler/syntax_validation.c \
			$(SRC_PATH)/510_errors_handler/syntax_validation_2.c \
			$(SRC_PATH)/510_errors_handler/print_errors_exit_failure.c \
			$(SRC_PATH)/510_errors_handler/print_errors_misuse.c \
			$(SRC_PATH)/510_errors_handler/print_errors_fatal_signal.c \
			$(SRC_PATH)/510_errors_handler/print_errors_utils.c \
			$(SRC_PATH)/520_tokenization/tokens_process.c \
			$(SRC_PATH)/520_tokenization/tokens_utils.c \
			$(SRC_PATH)/520_tokenization/tokens_utils_2.c \
			$(SRC_PATH)/520_tokenization/tokens_count.c \
			$(SRC_PATH)/520_tokenization/tokens_split.c \
			$(SRC_PATH)/520_tokenization/tokens_split_2.c \
			$(SRC_PATH)/530_expansion/expand.c \
			$(SRC_PATH)/530_expansion/expand_handle_dollar.c \
			$(SRC_PATH)/600_exec/exec.c \
			$(SRC_PATH)/600_exec/exec_utils.c \
			$(SRC_PATH)/610_builtins/cd.c \
			$(SRC_PATH)/610_builtins/echo.c \
			$(SRC_PATH)/610_builtins/env.c \
			$(SRC_PATH)/610_builtins/pwd.c \
			$(SRC_PATH)/610_builtins/export.c \
			$(SRC_PATH)/610_builtins/unset.c \
			$(SRC_PATH)/610_builtins/exit.c \
			$(SRC_PATH)/611_builtins_utils/env_utils.c \
			$(SRC_PATH)/611_builtins_utils/export_utils.c \
			$(SRC_PATH)/611_builtins_utils/export_print.c \
			$(SRC_PATH)/611_builtins_utils/cd_and_pwd_utils.c \
			$(SRC_PATH)/620_execve/execve.c \
			$(SRC_PATH)/620_execve/execve_utils.c \
			$(SRC_PATH)/620_execve/path_errors.c \
			$(SRC_PATH)/630_redirects/exec_redirection.c \
			$(SRC_PATH)/630_redirects/exec_redirection_utils.c \
			$(SRC_PATH)/630_redirects/exec_redirection_utils_2.c \
			$(SRC_PATH)/640_pipes/exec_pipes_child.c \
			$(SRC_PATH)/640_pipes/exec_pipes_utils.c \
			$(SRC_PATH)/640_pipes/exec_pipes.c \
			$(SRC_PATH)/640_pipes/exec_pipes_utils_2.c \
			$(SRC_PATH)/650_heredoc/heredoc_syntax.c \
			$(SRC_PATH)/650_heredoc/heredoc_utils.c \
			$(SRC_PATH)/650_heredoc/heredoc_input.c \
			$(SRC_PATH)/650_heredoc/heredoc_input_2.c \
			$(SRC_PATH)/650_heredoc/heredoc_tempfile.c \
			$(SRC_PATH)/700_utils_other/variable_utils.c \
			$(SRC_PATH)/700_utils_other/variable_utils_2.c \
			$(SRC_PATH)/700_utils_other/check_type_functions.c \
			$(SRC_PATH)/700_utils_other/safe_functions.c \
			$(SRC_PATH)/700_utils_other/safe_functions_2.c \
			$(SRC_PATH)/800_clean/clean.c \
			$(SRC_PATH)/800_clean/free.c

OBJS        = $(SRCS:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

#------------------------------------------------------------------------------#
#                             FLAGS & COMMANDS                                 #
#------------------------------------------------------------------------------#

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
RM          = rm -fr
MKDIR       = mkdir -p
INCLUDES    = -I$(INC_PATH) -I$(READLINE_PATH)/include
LDFLAGS     = -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline -lncurses
MAKE_LIBFT  = $(MAKE) -C $(LIBFT_PATH)

# Auto-detect readline path (macOS Homebrew or Linux default)
READLINE_PATH ?= $(shell [ "$(OS)" = "Darwin" ] && echo "/opt/homebrew/opt/readline" || echo "/usr")

# Valgrind options
V_ARGS      = --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp

#------------------------------------------------------------------------------#
#                                    RULES                                     #
#------------------------------------------------------------------------------#

all: deps $(NAME)
	@printf "\n${GREEN}${BOLD}${CHECK} Build completed successfully!${RESET}\n"

$(NAME): $(OBJS) $(LIBFT_ARC) | $(BUILD_PATH)
	@printf "${CYAN}${DIM}Linking minishell...${RESET}\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	@printf "${GREEN}${BOLD}${CHECK} Minishell compiled!${RESET}\n"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS) | $(BUILD_PATH)
	@$(MKDIR) $(@D)
	@printf "${CYAN}${DIM}Compiling: ${WHITE}%-35s${RESET}\r" "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_PATH):
	@printf "${BLUE}${BOLD}${BUILD} Creating build directory...${RESET}\n"
	@$(MKDIR) $(BUILD_PATH)
	@printf "${GREEN}${CHECK} Build directory ready${RESET}\n"

$(LIBFT_ARC):
	@printf "${CYAN}${BOLD}${BUILD} Building Libft...${RESET}\n"
	@$(MAKE_LIBFT)
	@printf "${GREEN}${CHECK} Libft compiled at ${WHITE}$(LIBFT_ARC)${RESET}\n"

deps: check_tools
	@if [ ! -d "$(LIBFT_PATH)" ]; then ($(MAKE) get_libft) ; \
	else (printf "${GREEN}${BOLD}${ROCKET} ${WHITE}$(LIBFT_ARC) found${RESET}\n"); fi

get_libft:
	@printf "${CYAN}${BOLD}${BOOK} Cloning Libft...${RESET}\n"
	@git clone https://github.com/m3irel3s/42_Libft $(LIBFT_PATH) || (printf "${RED}${BOLD}${CROSS} Failed to clone Libft${RESET}\n" && exit 1)
	@printf "${GREEN}${BOLD}${CHECK} Libft downloaded${RESET}\n"

#------------------------------------------------------------------------------#
#                                TESTING RULES                                 #
#------------------------------------------------------------------------------#

val: deps $(NAME)
	@printf "${BLUE}${BOLD}Running Valgrind...${RESET}\n"
	@valgrind $(V_ARGS) ./$(NAME)

vgdb: deps $(NAME)
	@printf "${BLUE}${BOLD}Running Valgrind with GDB...${RESET}\n"
	@valgrind --vgdb-error=0 $(V_ARGS) ./$(NAME)

gdb: all
	@printf "${BLUE}${BOLD}Launching GDB...${RESET}\n"
	@gdb -tui -q ./$(NAME) -x .gdbinit

test: all
	@printf "${BLUE}${BOLD}Testing minishell...${RESET}\n"
	@./$(NAME)

#------------------------------------------------------------------------------#
#                                CLEANING RULES                                #
#------------------------------------------------------------------------------#

clean:
	@printf "${YELLOW}${BOLD}${CLEAN} Cleaning object files...${RESET}\n"
	@$(RM) $(OBJS)
	@printf "${GREEN}${BOLD}${CHECK} Object files removed${RESET}\n"

fclean: clean
	@printf "${YELLOW}${BOLD}${CLEAN} Removing all build artifacts...${RESET}\n"
	@$(RM) $(NAME) $(BUILD_PATH) $(LIBFT_PATH)
	@printf "${GREEN}${BOLD}${CHECK} Full cleanup completed${RESET}\n"

re: fclean all
	@printf "${GREEN}${BOLD}${ROCKET} Rebuild finished${RESET}\n"

#------------------------------------------------------------------------------#
#                                NORMINETTE                                    #
#------------------------------------------------------------------------------#

norm:
	@printf "${BLUE}${BOLD}Checking Norminette...${RESET}\n"
	@command -v norminette >/dev/null || (printf "${RED}${BOLD}${CROSS} Norminette not found${RESET}\n" && exit 1)
	@FILES=$$(find . -name "*.c" -o -name "*.h"); \
	if [ -n "$$FILES" ]; then (norminette $$FILES | awk '/Error:/ {print "$(RED)$(BOLD)" $$0 "$(RESET)"; errors++} /: OK!/ {print "$(GREEN)" $$0 "$(RESET)"} END {if (errors) print "$(RED)$(BOLD)$(CROSS) " errors " errors found$(RESET)"; else print "$(GREEN)$(BOLD)$(CHECK) No errors found$(RESET)"}') ; \
	else (printf "${YELLOW}${BOLD}⚠️ No files to check${RESET}\n"); fi

#------------------------------------------------------------------------------#
#                           CHECK EXTERNAL FUNCTIONS                           #
#------------------------------------------------------------------------------#

check_external_functions: all
	@printf "${BLUE}${BOLD}Checking External Functions...${RESET}\n"
	@ALLOWED_RL="readline rl_clear_history rl_on_new_line rl_replace_line rl_redisplay add_history"; \
	[ "$(OS)" = "Darwin" ] && (otool -I -V ./$(NAME) | grep -E '^[0-9]+.*_' | awk '{print $$NF}') || \
	[ "$(OS)" = "Linux" ] && (nm -u ./$(NAME) | awk '/^[[:space:]]*U /{print $$2}') || \
	(printf "${RED}${BOLD}${CROSS} Unsupported OS: $(OS)${RESET}\n" && exit 1) | \
	grep -v "__" | sort -u | awk '{if (/^_rl_/ && !index("'"$$ALLOWED_RL"'", substr($$0,2))) next; orig=$$0; sub(/^_/, "", $$0); print orig" "$$0}' > .used.tmp
	@echo "$(ALLOWED_FUNCS)" | tr ' ' '\n' | sort > .allowed.tmp
	@printf "${CYAN}${DIM}Scanning...${RESET}\n"
	@awk 'NR==FNR {allowed[$$0]; next} {orig=$$1; stripped=$$2; printf "  %s%-30s (", (stripped in allowed ? "$(GREEN)$(CHECK) " : "$(RED)$(CROSS) "), orig; if (stripped in allowed) print "USED/ALLOWED)$(RESET)"; else {print "FORBIDDEN)$(RESET)"; exit 1}}' .allowed.tmp .used.tmp || (printf "\n${RED}${BOLD}${CROSS} Forbidden functions detected${RESET}\n" && exit 1)
	@awk '{print $$2}' .used.tmp | sort -u | comm -23 .allowed.tmp - | awk '{print "  $(YELLOW)$(CHECK) _" $$1 "                         (ALLOWED/NOT USED)$(RESET)"}'
	@printf "${GREEN}${BOLD}${CHECK} All functions allowed${RESET}\n"
	@$(RM) .used.tmp .allowed.tmp

#------------------------------------------------------------------------------#
#                                UTILITY RULES                                 #
#------------------------------------------------------------------------------#

check_tools:
	@command -v git >/dev/null || (printf "${RED}${BOLD}${CROSS} Git not found${RESET}\n" && exit 1)
	@command -v $(CC) >/dev/null || (printf "${RED}${BOLD}${CROSS} Compiler $(CC) not found${RESET}\n" && exit 1)

.PHONY: all clean fclean re norm check_external_functions deps get_libft val vgdb gdb test check_tools
