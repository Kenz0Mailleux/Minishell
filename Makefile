NAME = minishell

SRCS = 	main.c \
		srcs/parsing/init_token.c \
		srcs/parsing/lexer.c \
		srcs/parsing/parse.c \
		srcs/utils/free.c \

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -Llibft -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libfinal.a

RM = rm -rf

all: $(LIBFT) ${NAME}

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${LDFLAGS} -o ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@${RM} ${NAME}
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
