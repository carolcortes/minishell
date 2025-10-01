# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 22:54:08 by cade-oli          #+#    #+#              #
#    Updated: 2025/09/30 23:15:08 by cgross-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#
SRC_PATH		= src
INC_PATH		= inc
BUILD_PATH		= .build
LIBFT_PATH		= libft

FILES			= 	main.c main_ext.c signals.c utils.c expand.c free.c \
					parsing/tokens.c parsing/pipeline.c parsing/pipeline_ext.c parsing/redirections.c \
					parsing/tokens_ext1.c parsing/tokens_ext2.c parsing/tokens_ext3.c \
					execution/execute_pipeline.c execution/execute_pip_ext1.c execution/execute_pip_ext2.c \
					execution/external.c execution/utils.c execution/path.c \
					execution/redirections.c execution/redirections_ext.c execution/heredoc.c

BUILTINS		= 	exec_builtin.c ft_exit.c ft_echo.c ft_cd.c ft_pwd.c ft_env.c \
					ft_export.c ft_export_ext.c ft_unset.c environment.c

SRCS			= 	$(addprefix $(SRC_PATH)/, $(FILES)) \
					$(addprefix $(SRC_PATH)/builtins/, $(BUILTINS))

OBJS			= $(SRCS:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
CFLAGS	+= -g
CFLAGS	+= -I$(INC_PATH) -I$(LIBFT_PATH)
LDFLAGS = -lreadline -lhistory -lncurses # readline e suas dependências
# sudo apt-get install libreadline-dev

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#
RM			= rm -rf
MKDIR_P		= mkdir -p

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ minishell Compilation Rules 🏗

all: $(NAME)		## Compile All

$(NAME): $(BUILD_PATH) $(OBJS) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) $(OBJS) \
	$(LIBFT_PATH)/libft.a -I$(LIBFT_PATH) \
	-o $(NAME) $(LDFLAGS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@$(MKDIR_P) $(dir $@)  # ⬅️ CRIA O SUBDIRETÓRIO NECESSÁRIO
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)
	$(MKDIR_P) $(BUILD_PATH)/builtins
	@echo "* $(YEL)Creating $(BUILD_PATH) folder:$(D) $(_SUCCESS)"

##@ Dependencies Rules 📦

$(LIBFT_PATH)/libft.a:	## Compile libft if needed
	@echo "* $(CYA)Compiling libft...$(D)"
	@$(MAKE) -C $(LIBFT_PATH) extra
	@echo "* $(GRN)libft compiled successfully!$(D)"

deps:			## Compile dependencies (libft)
	@echo "* $(CYA)Compiling libft...$(D)"
	@$(MAKE) -C $(LIBFT_PATH) extra
	@echo "* $(GRN)libft compiled successfully!$(D)"

##@ Clean-up Rules 󰃢
clean:			## Clean object files
	$(RM) $(BUILD_PATH)

fclean: clean		## Full clean (objects + executable)
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all		## Clean and rebuild everything

help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(MAG)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(MAG)%-15s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile
## Tweaked from source:
### https://www.padok.fr/en/blog/beautiful-makefile-awk

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#
# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
