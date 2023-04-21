/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/21 17:52:38 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include<sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

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
t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell);
void	builtins(char **cmds, int words);
//Parser
void	parser(t_cmds *cmds, t_mshell *mshell);
#endif // MINISHELL_H
