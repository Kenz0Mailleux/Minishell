# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 17:24:07 by marykman          #+#    #+#              #
#    Updated: 2024/11/27 12:50:39 by nicolive         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------------------------------Colors------------------------------------

RED					:=	[38;5;9m
GREEN				:=	[38;5;10m
BLUE				:= 	[38;5;14m
YELLOW				:=	[38;5;226m
RESET				:=	[38;5;7m
PREFIX				=	[${YELLOW}${NAME}${RESET}]	

# ---------------------------------Compilation---------------------------------

CC					:=	@gcc
CFLAGS				:=	-Wall -Wextra -Werror -g -fsanitize=address
RM					:=	@rm -f

# ---------------------------------Librairies----------------------------------

FT_FOLDER			:=	libs/libft

FT					:=	${FT_FOLDER}/libft.a

MAKE_FT				:=	@make -s -C ${FT_FOLDER}

INCLUDES			:=	-I ${FT_FOLDER}/includes \
						-I ./includes
LIBRARIES			:=	-L./${FT_FOLDER} -lft \
						-lreadline

# --------------------------------Source files---------------------------------

NAME = minishell

FILES				:=	main.c
FILES_BUILTINS		:=	ft_echo.c \
						ft_cd.c \
						ft_pwd.c \
						ft_export.c \
						ft_unset.c \
						ft_env.c \
						ft_exit.c
FILES_ENV			:=	init_env.c\
						expander.c 
FILES_EXEC			:=
FILES_PARSING		:=	init_token.c \
						lexer.c \
						parse.c
FILES_UTILS			:=	free.c
FILES_SIGNALS		:=	signals.c
FILES_GNL			:=	get_next_line_utils.c \
						get_next_line.c

SRCS				:=	$(addprefix srcs/,${FILES})
SRCS				+=	$(addprefix srcs/builtins/,${FILES_BUILTINS})
SRCS				+=	$(addprefix srcs/env/,${FILES_ENV})
SRCS				+=	$(addprefix srcs/exec/,${FILES_EXEC})
SRCS				+=	$(addprefix srcs/parsing/,${FILES_PARSING})
SRCS				+=	$(addprefix srcs/utils/,${FILES_UTILS})
SRCS				+=	$(addprefix srcs/signals/,${FILES_SIGNALS})
SRCS				+=	$(addprefix srcs/gnl/,${FILES_GNL})


OBJS				:=	$(patsubst srcs%.c, objs%.o, ${SRCS})

# Header files
FILES				:=	minishell.h \
						builtins.h \
						env.h \
						exec.h \
						parsing.h \
						utils.h \
						signaling.h \
						get_next_line.h 
						
HEADERS				:=	$(addprefix includes/, ${FILES})

# -----------------------------------Rules-------------------------------------

objs/%.o:	srcs/%.c ${HEADERS}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	@echo "${PREFIX}Compilation of $<..."

$(NAME):	${FT} ${OBJS} ${HEADERS}
	${CC} ${CFLAGS} ${OBJS} ${LIBRARIES} -o ${NAME}
	@echo "${PREFIX}${GREEN}${NAME} compiled!"

$(FT):
	${MAKE_FT}

all:		${NAME}

clean:
	${MAKE_FT} clean
	${RM} ${OBJS}
	@echo "${PREFIX}${BLUE}Cleaning object files...${RESET}"

fclean:
	${MAKE_FT} fclean
	${RM} ${NAME} ${OBJS}
	@echo "${PREFIX}${RED}Full clean.${RESET}"

re: fclean all

.PHONY: all clean fclean re
