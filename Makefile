# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 17:24:07 by marykman          #+#    #+#              #
#    Updated: 2024/11/28 16:05:08 by nicolive         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m


LINK = -L$(READLIB) -I$(READINC) -lreadline

NAME = minishell

LIBFT = lib/libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS_DIR = srcs/
OBJS_DIR = obj/

SRCS =	srcs/main.c \
	srcs/builtins/ft_cd.c srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c srcs/builtins/ft_export.c \
	srcs/builtins/ft_pwd.c srcs/builtins/ft_unset.c \
	srcs/env/expander.c srcs/env/init_env.c \
	srcs/exec/builtin.c srcs/exec/error_exec.c srcs/exec/exec.c srcs/exec/expand.c srcs/exec/heredoc.c srcs/exec/path.c \
	srcs/exec/redirection.c srcs/exec/utils_exec.c \
	srcs/gnl/get_next_line_utils.c srcs/gnl/get_next_line.c \
	srcs/parsing/init_token.c srcs/parsing/lexer.c srcs/parsing/parse.c  \
	srcs/signals/signals.c \
	srcs/utils/free.c srcs/utils/utils.c \
	srcs/utils/ft_printf/char_cvrt.c srcs/utils/ft_printf/ft_printf.c srcs/utils/ft_printf/hex_cvrt.c srcs/utils/ft_printf/nbr_cvrt.c srcs/utils/ft_printf/ptr_cvrt.c srcs/utils/ft_printf/utils.c 


OBJ = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

OBJD = $(SRCS:$(SRCS_DIR)%.c=$(DEBUG_DIR)%.o)

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	@printf "                                               							   \r"
	@echo "\033[0;34m                 																 "
	@echo "\033[0;34m    	 ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗      "
	@echo "\033[0;34m  	 ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║      "
	@echo "\033[0;34m 	 ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║      "
	@echo "\033[0;34m 	 ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║      "
	@echo "\033[0;34m 	 ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗ "
	@echo "\033[0;34m 	 ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝ "
	@echo "\033[0;34m                 																 "
	@$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(LINK) -g -fsanitize=address -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/env
	@mkdir -p $(OBJS_DIR)/exec
	@mkdir -p $(OBJS_DIR)/gnl
	@mkdir -p $(OBJS_DIR)/parsing
	@mkdir -p $(OBJS_DIR)/signals
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/utils/ft_printf
	@$(CC) -o $@ -c $<

$(DEBUG_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(DEBUG_DIR)
	@mkdir -p $(DEBUG_DIR)/builtins
	@mkdir -p $(DEBUG_DIR)/env
	@mkdir -p $(DEBUG_DIR)/exec
	@mkdir -p $(DEBUG_DIR)/gnl
	@mkdir -p $(DEBUG_DIR)/parsing
	@mkdir -p $(DEBUG_DIR)/signals
	@mkdir -p $(DEBUG_DIR)/utils
	@$(CC) -o $@ -c $<

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(NC)"
	@make -C libft/

clean :
	@make clean -C libft
	@$(RM) obj/**/*.o
	@$(RM) obj_debug/**/*.o
	@$(RM) obj/minishell.o
	@$(RM) -r obj

fclean : clean
	@make fclean -C libft
	@$(RM) lib/
	@$(RM) $(NAME)

re : fclean all
	@$(RM) $(DEBUG)
