SRCS = miniRT.c vector.c
NAME = miniRT
MLX = -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror
CC = gcc


all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(MLX) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re