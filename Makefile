# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/14 13:55:04 by xchalle           #+#    #+#              #
#    Updated: 2021/12/03 10:10:28 by xchalle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	src/main.c \
	src/thread.c \
	src/utils.c \

NAME = philo
CFLAGS = -Wall -Werror -Wextra -I./include -pthread
CC = gcc
OBJ = $(SRC:.c=.o) 

all:	$(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
