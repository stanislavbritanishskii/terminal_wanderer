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
FLAGS	:= -Wall -Wextra -Werror
# FLAGS	:= -I lib/include/ -I lib/ -I src/

OBJ_DIR	:= obj/
SRC_DIR	:= src/
NAME	:= terminal_engine.a

SRC		:= get_next_line_bonus.c\
           get_next_line_utils_bonus.c\
           itoa.c\
           object.c\
           pressed_process.c\
           scene.c\
           state_changes.c\
           utils.c\
           functions.c\
           init.c

				
OBJS = $(SRC:.c=.o)

all: libft libmlx $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) 
	ar rcs $(NAME) $(OBJS)

$(OBJS): %.o : %.c
	@$(CC) $(CFLAGS) -c $^ -o $@


$(OBJ_DIR): 
	mkdir obj

norm:
	norminette $(FIL) cub.h

clean:
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft libmlx

