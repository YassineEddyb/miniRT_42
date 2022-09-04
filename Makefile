# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 19:35:33 by ael-bach          #+#    #+#              #
#    Updated: 2022/09/03 18:53:43 by yed-dyb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS =	./srcs/get_next_line/get_next_line.c\
		./srcs/get_next_line/get_next_line_utils.c\
		./srcs/parser/parser.c ./srcs/parser/ft_atof.c ./srcs/parser/Ambient_light.c\
		./srcs/parser/element.c ./srcs/parser/split_spaces.c\
		./srcs/parser/camera.c ./srcs/parser/light.c ./srcs/parser/sphere.c\
		./srcs/parser/helper.c\

SRCS_RENDER = 	miniRT.c\
		vector.c\
		matrix.c\
		matrix_helpers.c\
		matrix_transfomations.c\
		ray_functions.c\
		sphere.c mutrix_inits.c\
		color.c\
		light.c\
		material.c\
		world.c\
		camera.c\
		shadows.c\
		render.c\
		planes.c\
		cylinder.c\
		vector_helpers.c\
		mlx_helpers.c\
		free_leaks.c

NAME = miniRT
MLX = -lmlx -framework OpenGL -framework AppKit

OBJS = ${SRCS:.c=.o}

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

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
