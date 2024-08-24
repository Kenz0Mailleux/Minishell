NAME = minishell

SRCS = main.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lreadline -lhistory

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${LDFLAGS} -o ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean: 
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
