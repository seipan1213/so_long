NAME		=	so_long
SRCSDIR		=	./srcs

SRCS_NAME	=	main.c
SRCS		=	${addprefix ${SRCSDIR}/, ${SRCS_NAME}}
OBJS		=	${SRCS:.c=.o}
DEPS		=	${OBJS:%.o=%.d}

MLX_PATH	:=	./minilibx-linux
MLX_LIB		:=	-L$(MLX_PATH) -lmlx

INCLUDES	=	-I ./includes
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDES} -o $@

.c.o:
	${CC} ${CFLAGS} $< -c ${INCLUDES} -o $@

clean:
	${RM} ${OBJS} ${DEPS}

fclean: clean
	${RM} ${NAME}

re: fclean all

${MLX_PATH}:
	git clone https://github.com/42Paris/minilibx-linux.git ${MLX_PATH}
	make -C ${MLX_PATH}

.PHONY: all clean fclean re