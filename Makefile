# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 19:35:33 by ael-bach          #+#    #+#              #
#    Updated: 2022/09/04 19:27:59 by yed-dyb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS =	./srcs/get_next_line/get_next_line.c\
		./srcs/get_next_line/get_next_line_utils.c\
		./srcs/parser/parser.c ./srcs/parser/ft_atof.c ./srcs/parser/Ambient_light.c\
		./srcs/parser/element.c ./srcs/parser/split_spaces.c\
		./srcs/parser/camera.c ./srcs/parser/light.c ./srcs/parser/sphere.c\
		./srcs/parser/helper.c\

SRCS_RENDER = 	./srcs/render/miniRT.c\
		./srcs/render/vector.c\
		./srcs/render/matrix.c\
		./srcs/render/matrix_helpers.c\
		./srcs/render/matrix_transfomations.c\
		./srcs/render/ray_functions.c\
		./srcs/render/sphere.c\
		./srcs/render/mutrix_inits.c\
		./srcs/render/color.c\
		./srcs/render/light.c\
		./srcs/render/material.c\
		./srcs/render/world.c\
		./srcs/render/camera.c\
		./srcs/render/shadows.c\
		./srcs/render/render.c\
		./srcs/render/planes.c\
		./srcs/render/cylinder.c\
		./srcs/render/vector_helpers.c\
		./srcs/render/mlx_helpers.c\
		./srcs/render/free_leaks.c

NAME = miniRT
MLX = -lmlx -framework OpenGL -framework AppKit

OBJS = ${SRCS:.c=.o}

CC = @cc

CFLAGS = -Wall -Wextra -Werror

RM = @rm -f

libft = srcs/Libft/libft.a

${NAME} : ${SRCS} ${SRCS_RENDER}
	@make -C srcs/Libft
	${CC} ${CFLAGS} ${SRCS} ${libft} $(SRCS_RENDER) $(MLX) -o ${NAME}
	@tput setaf 2; echo "miniRT IS READY"

all : ${NAME}

clean :
	${RM} ${OBJS}
	@make clean -C srcs/Libft
	@tput setaf 1; echo "OBJECTS REMOVED"

fclean : clean
	${RM} ${NAME}
	${RM} ${libft}
	@tput setaf 1; echo "miniRT REMOVED"

re : fclean all

.phony: all clean fclean re
