# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 18:36:00 by cjaimes           #+#    #+#              #
#    Updated: 2019/11/20 19:55:30 by cjaimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

MLX_NAME	=	libmlx.a

MLX_DIR		=	minilibx_opengl

SRCS		=	main.c \
				math_functions.c

OBJ			=	${SRCS:.c=.o}

NAME	=	miniRT

RM			=	rm -f

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

MLX_FLAGS	=	-lmlx -framework OpenGL -framework AppKit

T		=	$(words ${OBJ})
N		=	0
C		=	$(words $N)${eval N := X $N}
_CYAN	=	\033[36m
_GREEN	=	\033[32m
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

all:	${NAME}

${MLX_DIR}${MLX_NAME}:
	${MAKE} -C ${MLX_DIR}

%.o :	%.c
			@${CC} ${CFLAGS} -I ${MLX_DIR} -c $< -o ${<:.c=.o}
			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}:	${MLX_DIR}${MLX_NAME} ${OBJ}
	${CC} ${CFLAGS} -I ${MLX_DIR} -o ${NAME} ${OBJ} -L.${MLX_DIR}/${MLX_NAME} ${MLX_FLAGS}

run : all
	./${NAME}

bonus: all

clean:
	${RM} ${OBJ}
	${MAKE} -C ${MLX_DIR} clean

fclean:	clean
	${RM} ${NAME}
	${RM} ${MLX_DIR}/${MLX_NAME}

re: fclean all