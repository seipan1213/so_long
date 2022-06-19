NAME		=	so_long
SRCSDIR		=	./srcs

SRCS_NAME	=	main.c mlx_utils.c utils.c
SRCS		=	${addprefix ${SRCSDIR}/, ${SRCS_NAME}}
OBJS		=	${SRCS:.c=.o}
DEPS		=	${OBJS:%.o=%.d}

LIBFT_PATH	=	./libft
LIBFT		=	${LIBFT_PATH}/libft.a

MLX_PATH	:=	./minilibx-linux
MLX_LIB		:=	-L$(MLX_PATH) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz

INCLUDES	=	-I ./includes -I ${LIBFT_PATH}
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP

all: ${NAME}

${LIBFT}:
	${MAKE} -C ${LIBFT_PATH}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX_LIB} ${INCLUDES} -o $@

.c.o:
	${CC} ${CFLAGS} $< -c ${INCLUDES} -o $@

clean:
	${RM} ${OBJS} ${DEPS}
	${MAKE} clean -C ${LIBFT_PATH}


fclean: clean
	${RM} ${NAME}
	${MAKE} fclean -C ${LIBFT_PATH}

re: fclean all

${MLX_PATH}:
	git clone https://github.com/42Paris/minilibx-linux.git ${MLX_PATH}
	make -C ${MLX_PATH}

.PHONY: all clean fclean re