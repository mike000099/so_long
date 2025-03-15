# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 18:59:43 by yseddouk          #+#    #+#              #
#    Updated: 2025/03/13 00:27:30 by yseddouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = \
main.c\
validate_map.c\
utils_one.c\
utils_two.c\
game_loop_one.c\
game_loop_two.c\
read_map.c\
validate_path.c\
validate_path_two.c\
graphics.c\
./get_next_line/get_next_line.c
OBJ = $(SRC:.c=.o)
PRINTF_DIR = ./ft_printf
LIBFT_DIR = ./libft
INCLUDES = -I$(PRINTF_DIR) -I$(LIBFT_DIR) -I. -I./minilibx-linux -I./get_next_line

LDFLAGS = -L$(PRINTF_DIR) -L$(LIBFT_DIR) -L./minilibx-linux
LIBMLX = -lmlx -lm -lX11 -lXext

LDLIBS = -lftprintf -lft $(LIBMLX)
NAME = so_long

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

