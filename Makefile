NAME		=	so_long
SRCSDIR		=	./srcs

SRCS_NAME	=	main.c
SRCS		=	${addprefix ${SRCSDIR}, ${SRCS_NAME}}
OBJS		=	${SRCS:.c=.o}
DEPS		=	${OBJS:%.o=%.d}

INCLUDES	=	-I ./includes
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@

.c.o:
	${CC} ${CFLAGS} $< -c ${INCLUDES} -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

-include ${DEPS}

${MLX_PATH}:
	git clone https://github.com/42Paris/minilibx-linux.git ${MLX_PATH}
	make -C ${MLX_PATH}

.PHONY: all clean fclean re