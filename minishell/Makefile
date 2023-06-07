# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:37:51 by brumarti          #+#    #+#              #
#    Updated: 2023/06/07 11:53:36 by brumarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./includes -g

SRC = main.c \
		srcs/bash/cmds.c \
		srcs/bash/words.c \
		srcs/bash/lexer.c \
		srcs/bash/errors.c \
		srcs/utils/utils.c \
		srcs/bash/parser.c \
		srcs/bash/expand.c \
		srcs/builtins/pipe.c \
		srcs/builtins/builtins.c \
		srcs/builtins/executable.c \
		srcs/utils/ft_replace_env.c \
		srcs/utils/minishell_loop.c

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