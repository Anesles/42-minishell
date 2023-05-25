# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:37:51 by brumarti          #+#    #+#              #
#    Updated: 2023/05/25 17:43:24 by brumarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./includes -g

SRC = main.c \
		srcs/utils.c \
		srcs/lexer.c \
		srcs/cmds.c	\
		srcs/builtins/builtins.c \
		srcs/parser.c \
		srcs/executable.c \
		srcs/env_var.c \
		srcs/pipe.c \
		srcs/words.c \
		srcs/expand.c

OBJ = $(SRC:.c=.o)

LIBFTPATH = ./libft/

LIBFTNAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFTPATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTPATH)$(LIBFTNAME) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(LIBFTPATH)$(LIBFTNAME) $(NAME)

re: fclean all

.SILENT: