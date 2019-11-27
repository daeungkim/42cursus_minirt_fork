# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesarsld <cesarsld@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 18:36:00 by cjaimes           #+#    #+#              #
#    Updated: 2019/11/27 19:43:37 by cesarsld         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

MLX_NAME	=	libmlx.a

MLX_DIR		=	minilibx_opengl

LIB_NAME	=	libft.a

LIB_DIR		=	libft

SRCS		=	main.c \
				math_functions.c \
				parser.c \
				factories.c \
				vector_maths.c \
				vector_maths2.c \
				vector_maths3.c \
				colour_functions.c

OBJ			=	${SRCS:.c=.o}

NAME	=	miniRT

RM			=	rm -f

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g

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

${LIB_DIR}${LIB_NAME}:
	${MAKE} -C ${LIB_DIR}
	
.PHONY: dependencies
dependencies : ${LIB_DIR}${LIB_NAME} ${MLX_DIR}${MLX_NAME}

%.o :	%.c
			@${CC} ${CFLAGS} -I ${MLX_DIR} -I ${LIB_DIR}/includes -c $< -o ${<:.c=.o}
			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}:	${OBJ}
	${MAKE} -C ${MLX_DIR}
	${MAKE} -C ${LIB_DIR}
	#export DYLD_LIBRARY_PATH=${MLX_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -L${MLX_DIR} -lmlx -L${LIB_DIR} -lft ${MLX_FLAGS}

run : all
	./${NAME} scene.rt

bonus: all

clean:
	${RM} ${OBJ}
	${MAKE} -C ${MLX_DIR} clean
	${MAKE} -C ${LIB_DIR} clean

fclean:	clean
	${RM} ${NAME}
	${RM} ${MLX_DIR}/${MLX_NAME}
	${RM} ${LIB_DIR}/${LIB_NAME}

re: fclean all