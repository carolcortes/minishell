# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 10:20:02 by cade-oli          #+#    #+#              #
#    Updated: 2025/08/06 21:58:37 by cade-oli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
NAME = libft.a

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#


BUILD_PATH		= .build
LIBFT_PATH		= ./libft
GNL_PATH 		= ./get_next_line

FILES			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_strcmp.c
SRC_FILES		= $(addprefix $(LIBFT_PATH)/, $(FILES))
OBJ_FILES		= $(addprefix $(BUILD_PATH)/, $(notdir $(SRC_FILES:.c=.o)))

BONUS_FILES		= $(addprefix $(LIBFT_PATH)/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c)
BONUS_OBJ		= $(addprefix $(BUILD_PATH)/, $(notdir $(BONUS_FILES:.c=.o)))

H_FILE			= libft.h

GNL_FILES		= $(addprefix $(GNL_PATH)/, get_next_line.c get_next_line_utils.c)
GNL_OBJS		= $(addprefix $(BUILD_PATH)/, $(notdir $(GNL_FILES:.c=.o)))

#==============================================================================#
#                            COMPILER & FLAGS                                  #
#==============================================================================#
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I.

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#
RM 			= rm -rf
AR 			= ar rcs
MKDIR_P		= mkdir -p

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ libft Compilation Rules 🏗

all: $(NAME)	## Compile Basic libft

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)
	@echo "* $(BLUE)Creating $(BUILD_PATH) folder:$(RESET)"

$(BUILD_PATH)/%.o: $(LIBFT_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_PATH)/%.o: $(GNL_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(BUILD_PATH) $(OBJ_FILES)
	$(AR) $(NAME) $(OBJ_FILES)
	@echo "$(BLUE)📦 Creating library archive: $(NAME)$(RESET)"

bonus: $(BUILD_PATH) $(OBJ_FILES) $(BONUS_OBJ) ## Compile libft with bonus
	$(AR) $(NAME) $(OBJ_FILES) $(BONUS_OBJ)
	@echo "$(GREEN)✔ Bonus functions added to $(NAME)$(RESET)"

extra: $(BUILD_PATH) $(OBJ_FILES) $(BONUS_OBJ) $(GNL_OBJS) ## Compile libft with extra
	@echo "* $(BLUE)Archiving $(NAME) w/ extras$(RESET)"
	$(AR) $(NAME) $(OBJ_FILES) $(BONUS_OBJS) $(GNL_OBJS)
	@echo "* $(NAME) archived w/ extras $(CYAN)🖔$(RESET)"

clean: ## Clean libft binaries
	$(RM) $(OBJ_FILES) $(BONUS_OBJ) $(GNL_OBJS)
	@echo "🧹$(MAGENTA) Object files cleaned.$(RESET)"

fclean: clean ## Clean libft archive
	$(RM) $(NAME)
	$(RM) $(BUILD_PATH)
	@echo "🧹$(MAGENTA) Library file cleaned.$(RESET)"

re: ## Clean and re-compile libft
	@echo "$(CYAN)🔄 Rebuilding project...$(RESET)"
	$(MAKE) --no-print-directory fclean all

##@ Help 󰛵

help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(GRN)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(GRN)%-15s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile
## Tweaked from source:
### https://www.padok.fr/en/blog/beautiful-makefile-awk

.PHONY: all bonus extra clean fclean re help

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
GREEN = \033[0;32m
BLUE   = \033[0;34m
MAGENTA = \033[0;35m
CYAN   = \033[0;36m
RESET  = \033[0m
