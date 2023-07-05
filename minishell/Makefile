# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:37:51 by brumarti          #+#    #+#              #
#    Updated: 2023/06/14 16:06:35 by brumarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./includes -g -fsanitize=address

SRC = main.c \
		srcs/bash/lexer.c \
		srcs/bash/errors.c \
		srcs/utils/utils.c \
		srcs/bash/parser.c \
		srcs/utils/get_env.c \
		srcs/builtins/pipe.c \
		srcs/builtins/b_cd.c \
		srcs/bash/cmds/cmds.c \
		srcs/utils/clear_mem.c \
		srcs/builtins/b_echo.c \
		srcs/builtins/b_unset.c \
		srcs/bash/words/nalloc.c \
		srcs/builtins/exec_mul.c \
		srcs/builtins/b_export.c \
		srcs/builtins/builtins.c \
		srcs/bash/expand/expand.c \
		srcs/builtins/executable.c \
		srcs/utils/ft_replace_env.c \
		srcs/utils/minishell_loop.c \
		srcs/bash/cmds/alloc_words.c \
		srcs/builtins/builtins_aux.c \
		srcs/bash/words/init_words.c \
		srcs/bash/expand/get_nsize.c \
		srcs/builtins/b_export_neq.c \
		srcs/bash/words/valid_words.c \
		srcs/bash/cmds/alloc_redirs.c \
		srcs/bash/expand/expand_env.c \
		srcs/bash/words/words_utils.c

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

run: re
	clear && ./$(NAME)

.SILENT: