/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/25 17:42:34 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h> 
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_lexer
{
	char			*word;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_mshell
{
	int	n_cmds;
	int	current_cmd;
	int	fd[2];
	char **envior;
	char *PATH;
}	t_mshell;

typedef struct s_cmds t_cmds;

typedef struct s_cmds
{
	char			**words;
	int				count_words;
	void			(*built)(t_cmds *, t_mshell *);
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

//Utils
int		count_words(char **words);
void	clear_words(char **words, int n);
int		find_char(char *str, char c);
//Lexer
t_lexer	*init_lexer(char **words, int n);
//Cmds
t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell);
void	builtins(t_cmds *cmds, t_mshell *mshell);
//Parser
void	parser(t_cmds *cmds, t_mshell *mshell);
//Builtins
void	b_exit(int status);
//Executables
char 	**arraydup(char **old);
void	executables(char **cmd, t_mshell *mshell);
char	*get_path(char **pwd);
//Pipe
void	handle_pipe(t_mshell *mshell);
//Words
char	**init_words(char *str, t_mshell *mshell);
//Expand
char	*expand(char *str, t_mshell *mshell);
#endif // MINISHELL_H
