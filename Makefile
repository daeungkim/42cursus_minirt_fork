# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 18:36:00 by cjaimes           #+#    #+#              #
#    Updated: 2020/01/14 12:13:53 by cjaimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

MLX_NAME	=	libmlx.a

MLX_DIR		=	minilibx_opengl

LIB_NAME	=	libft.a

LIB_DIR		=	libft

OBJ_DIR		=	obj/

SRC_DIR		=	srcs/

INCLUDE		=	includes

SRC			=	main.c \
				bmp.c \
				render.c \
				inputs/events.c \
				inputs/camera.c \
				inputs/objects_rotation.c \
				inputs/objects_movement.c \
				inputs/objects_normal_calc.c \
				inputs/objects_normal_calc_2.c \
				parser/parser.c \
				parser/helper.c \
				parser/helper_2.c \
				parser/load_base.c \
				parser/load_basic_shapes.c \
				parser/load_complex_shapes.c \
				parser/load_composed_shapes.c \
				factories/base_factories.c \
				factories/simple_factories.c \
				factories/complex_factories.c \
				maths/quartic.c \
				maths/math_functions.c \
				maths/math_functions_2.c \
				maths/vector_maths/vector_maths.c \
				maths/vector_maths/vector_maths2.c \
				maths/vector_maths/vector_maths3.c \
				maths/vector_maths/vector_maths4.c \
				maths/colour_functions.c \
				maths/colour_functions_2.c \
				maths/ray_maths.c \
				maths/ray_maths_2.c \
				maths/light_maths.c \
				maths/geo_math/geo.c \
				maths/geo_math/sphere.c \
				maths/geo_math/plane.c \
				maths/geo_math/square.c \
				maths/geo_math/disk.c\
				maths/geo_math/cylinder.c \
				maths/geo_math/cone.c \
				maths/geo_math/triangle.c \
				maths/geo_math/torus.c \
				composed_shapes/dodecahedron/dodecahedron.c \
				composed_shapes/dodecahedron/dode_peak_1_5.c \
				composed_shapes/dodecahedron/dode_peak_6_10.c \
				composed_shapes/dodecahedron/dode_peak_11_12.c \
				composed_shapes/dodecahedron/dode_pl_pk.c \
				composed_shapes/pyramid/pyramid.c \
				composed_shapes/spherocylinder/spherocylinder.c \
				composed_shapes/cube/cube.c

SRCS		=	${addprefix ${SRC_DIR}, ${SRC}}

OBJS		=	${patsubst ${SRC_DIR}%.c,${OBJ_DIR}%.o,${SRCS}}

NAME		=	miniRT

RM			=	rm -f

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g -O3

MLX_FLAGS	=	-lmlx -framework OpenGL -framework AppKit

T		=	$(words ${OBJS})
N		=	0
C		=	$(words $N)${eval N := X $N}
_CYAN	=	\033[36m
_GREEN	=	\033[32m
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

all:	${NAME}

${OBJ_DIR}%.o :	${SRC_DIR}%.c
			@mkdir -p ${OBJ_DIR}
			@mkdir -p ${OBJ_DIR}parser
			@mkdir -p ${OBJ_DIR}maths
			@mkdir -p ${OBJ_DIR}inputs
			@mkdir -p ${OBJ_DIR}factories
			@mkdir -p ${OBJ_DIR}composed_shapes
			@mkdir -p ${OBJ_DIR}composed_shapes/dodecahedron
			@mkdir -p ${OBJ_DIR}composed_shapes/pyramid
			@mkdir -p ${OBJ_DIR}composed_shapes/spherocylinder
			@mkdir -p ${OBJ_DIR}composed_shapes/cube
			@mkdir -p ${OBJ_DIR}maths/geo_math
			@mkdir -p ${OBJ_DIR}maths/vector_maths
			@${CC} ${CFLAGS} -I ${INCLUDE} -I ${MLX_DIR} -I ${LIB_DIR}/includes -c $< -o $@
			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}: ${OBJS}
	${MAKE} -C ${MLX_DIR}
	${MAKE} -C ${LIB_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${MLX_DIR} -lmlx -L${LIB_DIR} -lft ${MLX_FLAGS}

run : all
	./${NAME} scenes/scene.rt

bonus: all

clean:
	${RM} ${OBJS}
	${MAKE} -C ${MLX_DIR} clean
	${MAKE} -C ${LIB_DIR} clean

fclean:	clean
	${RM} ${NAME}
	${RM} ${MLX_DIR}/${MLX_NAME}
	${RM} ${LIB_DIR}/${LIB_NAME}

re: fclean all