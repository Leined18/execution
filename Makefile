# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:34:27 by danpalac          #+#    #+#              #
#    Updated: 2024/11/11 17:24:32 by mvidal-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==========COLOURS=============================================================#

# Basic Colors
BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

# Bright Colors
BOLD_BLACK  = \033[1;30m
BOLD_RED    = \033[1;31m
BOLD_GREEN  = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE   = \033[1;34m
BOLD_MAGENTA= \033[1;35m
BOLD_CYAN   = \033[1;36m
BOLD_WHITE  = \033[1;37m

# Extended Colors (256 colors)
ORANGE      = \033[38;5;208m
WINE        = \033[38;5;88m
LIME        = \033[38;5;190m
TURQUOISE   = \033[38;5;38m
LIGHT_PINK  = \033[38;5;13m
DARK_GRAY   = \033[38;5;235m
LIGHT_RED   = \033[38;5;203m
LIGHT_BLUE  = \033[38;5;75m

BRIGHT_BLUE = \033[38;5;27m
BRIGHT_GREEN= \033[38;5;46m
BRIGHT_YELLOW=\033[38;5;226m
BRIGHT_CYAN = \033[38;5;51m
BRIGHT_WHITE= \033[38;5;231m

# Reseteo de color
NO_COLOR    = \033[0m
DEF_COLOR   = \033[0;39m
CLEAR_LINE  = \033[2K
MOVE_UP     = \033[1A

#==========NAMES===============================================================#

NAME		:= exe.a
EXE			:= exe

#==========DIRECTORIES=======================================================#

INC 			:= inc/
SRC_DIR 		:= src/
OBJ_DIR 		:= obj/
LIBFT_DIR		:= ../libft/

BUILTINS_DIR	:= builtins/
CMD_DIR			:= cmd/
ENV_DIR			:= env/


LIBFT		:= $(LIBFT_DIR)libft.a
INC_LIBFT		:= $(LIBFT_DIR)$(INC)
INCLUDES		:= $(INC)*.h $(BUILTINS_DIR)*.h $(CMD_DIR)*.h $(ENV_DIR)*.h $(INC_LIBFT)*.h

#==========COMMANDS============================================================#

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g3 #-fsanitize=address
RM			:= rm -rf
AR			:= ar rcs
LIB			:= ranlib
MKDIR 		:= mkdir -p
IFLAGS		:= -I$(INC) -I$(BUILTINS_DIR) -I$(CMD_DIR) -I$(ENV_DIR) -I$(INC_LIBFT)
LFLAGS		:= -L$(LIBFT_DIR) -L.

#==========SOURCES============================================================#

BUILTINS_FILES	:= ft_cd ft_echo ft_env 
CMD_FILES		:= 
ENV_FILES		:= env_init

#==========FILES==============================================================#

SRC_FILES+=$(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))
SRC_FILES+=$(addprefix $(CMD_DIR), $(CMD_FILES))
SRC_FILES+=$(addprefix $(ENV_DIR), $(ENV_FILES))

SRCS := $(addsuffix .c, $(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS := $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

#==========RULES==============================================================#

all: $(NAME)
-include $(DEPS)

$(OBJ_DIR)%.o: %.c Makefile
	@$(MKDIR) $(dir $@)	
	@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) -MP -MMD -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
$(NAME): $(LIBFT) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(LIB) $(NAME)
	@echo "$(BOLD_BLUE)[$(BRIGHT_GREEN)$(NAME)$(DEF_COLOR)$(BOLD_BLUE)] compiled!$(DEF_COLOR)"
	@echo "$(TURQUOISE)------------\n| Done! 👌 |\n------------$(DEF_COLOR)"
	@$(MKDIR) obj/inc/
	@cp -R $(INCLUDES) obj/inc/

$(EXE): $(NAME)
	@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) main.c $(NAME) -lft -o $(EXE)
	@echo "$(BOLD_BLUE)[$(BRIGHT_GREEN)$(EXE)$(DEF_COLOR)$(BOLD_BLUE)] compiled!$(DEF_COLOR)"
	@echo "$(TURQUOISE)------------\n| Done! 👌 |\n------------$(DEF_COLOR)"

$(LIBFT):
	@make -sC $(LIBFT_DIR)
	
clean:
	@$(RM) -rf $(OBJ_DIR) $(DEPS)
	@make clean -sC $(LIBFT_DIR)
	@echo "$(CYAN)[$(NAME)]:\tobject files $(GREEN) => Cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) -rf $(NAME) $(EXE)
	@make fclean -sC $(LIBFT_DIR)
	@echo "$(CYAN)[$(NAME)]:\tEXE. files $(GREEN) => Cleaned!$(DEF_COLOR)"

re: fclean all

.SILENT: all clean fclean
.PHONY: all clean fclean re bonus
