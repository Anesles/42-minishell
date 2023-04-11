/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/11 16:12:29 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct s_lexer
{
	char *word;
	struct	s_lexer *next;
	struct	s_lexer *prev;
} t_lexer;

//Utils
int		count_words(char **words);
void	clear_words(char **words, int n);
//Lexer
void	init_lexer(t_lexer **lexer, char **words);
void	clear_lexer(t_lexer **lexer, int n);

#endif // MINISHELL_H
