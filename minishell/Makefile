# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:37:51 by brumarti          #+#    #+#              #
#    Updated: 2023/04/12 15:44:29 by brumarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./includes

SRC = main.c \
		srcs/utils.c \
		srcs/lexer.c \
		srcs/cmds.c

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