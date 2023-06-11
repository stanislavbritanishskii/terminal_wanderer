# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 20:12:24 by sbritani          #+#    #+#              #
#    Updated: 2023/04/10 02:38:17 by dhendzel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -I lib/include/ -I lib/ -I src/
# FLAGS	:= -I lib/include/ -I lib/ -I src/

OBJ_DIR	:= obj/
SRC_DIR	:= src/
NAME	:= wanderer

SRC		:= checks.c \
			main.c \
			read_map.c \
			utils.c dict.c \
			textures.c \
			init.c \
			color.c \
			draw_wall.c \
			clean.c \
			create_map.c \
			move_rotate.c \
			map_check.c \
			math_utils.c \
			music.c
				
OBJS = $(FIL:.c=.o)
FIL =  $(addprefix src/, $(SRC)) 
libft_path=libs/libft/libft.a
terminal_path=libs/terminal_engine/terminal_engine.a

all: libft terminal $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) 
	$(CC) $(OBJS) $(libft_path) $(terminal_path) -o $(NAME) -lpthread -lm

$(OBJS): %.o : %.c
	gcc $(FLAGS) -c -o $@ $<


$(OBJ_DIR): 
	mkdir obj

libft:
	make --directory=./libs/libft

terminal:
	make --directory=./libs/terminal_engine

norm:
	norminette $(FIL) cub.h

clean:
	make clean --directory=libs/libft/
	make clean --directory=libs/terminal_engine/
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	make fclean --directory=libs/libft/
	make fclean --directory=libs/terminal_engine/
	rm -rf $(MLXLIB)/build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft terminal

