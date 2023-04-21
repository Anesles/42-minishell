/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/21 17:34:56 by brumarti         ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_lexer
{
	char *word;
	struct	s_lexer *next;
	struct	s_lexer *prev;
}	t_lexer;

typedef struct s_cmds
{
	char	**words;
	int		count_words;
	void	(*built)(char **, int);
	struct	s_cmds *next;
	struct	s_cmds *prev;
}	t_cmds;

typedef struct s_mshell
{
	int	n_cmds;
}	t_mshell;


//Utils
int		count_words(char **words);
void	clear_words(char **words, int n);
//Lexer
t_lexer	*init_lexer(char **words, int n);
//Cmds
t_cmds	*init_cmds(t_lexer *lexer);
void	builtins(char **cmds, int words);
//Parser
void	parser(t_cmds *cmds);
#endif // MINISHELL_H
