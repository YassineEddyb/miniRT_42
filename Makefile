# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 19:35:33 by ael-bach          #+#    #+#              #
#    Updated: 2022/07/22 15:18:23 by ael-bach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS =	./srcs/get_next_line/get_next_line.c\
		./srcs/get_next_line/get_next_line_utils.c\
		parser.c ./srcs/parser/ft_atof.c ./srcs/parser/Ambient_light.c\
		./srcs/parser/element.c ./srcs/parser/split_spaces.c\
		./srcs/parser/camera.c ./srcs/parser/light.c\

OBJS = ${SRCS:.c=.o}

CC = @cc

CFLAGS = -Wall -Wextra -Werror

RM = @rm -f

libft = srcs/Libft/libft.a

${NAME} : ${SRCS}
	@make -C srcs/Libft
	${CC}  ${CFLAGS} ${SRCS} ${libft} -o ${NAME} 
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