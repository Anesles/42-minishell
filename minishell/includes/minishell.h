/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/12 15:13:08 by brumarti         ###   ########.fr       */
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
}	t_lexer;

typedef struct s_cmds
{
	char	**words;
	struct s_cmds *next;
	struct s_cmds *prev;
}	t_cmds;

//Utils
int		count_words(char **words);
void	clear_words(char **words, int n);
//Lexer
void	init_lexer(t_lexer **lexer, char **words);
void	clear_lexer(t_lexer **lexer, int n);
//Cmds
void	init_cmds(t_lexer *lexer);

#endif // MINISHELL_H
