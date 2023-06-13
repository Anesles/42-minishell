/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:45:00 by brumarti         ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_lexer
{
	char			*word;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_mshell
{
	int		n_cmds;
	int		current_cmd;
	int		fd[2];
	int		save_fd[2];
	char	*path;
	char	**envior;
}	t_mshell;

typedef struct s_cmds	t_cmds;

typedef struct s_cmds
{
	char			**words;
	int				count_words;
	int				(*built)(t_cmds *, t_mshell *);
	char			*token;
	char			*redi;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

//Utils
int		count_words(char **words);
void	clear_words(char **words, int n);
int		find_char(char *str, char c);
int		is_redir(char *str);
int		is_builtins(char *str);
char	*ft_replace_env(char *str, char *substr, char *replace);
//Minishell_loop
void	minishell_loop(t_mshell *mshell);
//Lexer
t_lexer	*init_lexer(char **words, int n);
//Cmds
t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell);
int		builtins(t_cmds *cmds, t_mshell *mshell);
//Parser
void	parser(t_cmds *cmds, t_mshell *mshell);
//Builtins
void	b_exit(int status);
//B_unset
int		b_unset(char *variable, t_mshell *mshell);
//B_export
int		b_export(char *n_var, t_mshell *mshell);
//B_echo
int		b_echo(char **words, int max_words);
//B_cd
int		b_cd(char *direct, t_mshell *mshell);
//Executables
char	**arraydup(char **old);
void	executables(char **cmd, t_mshell *mshell);
char	*get_path(char **pwd);
//Pipe
void	handle_pipe(t_mshell *mshell);
void	reset_pipes(t_mshell *mshell);
void	token_less(t_cmds *cmds, int mode);
void	token_more(t_cmds *cmds, int mode);
//Words
char	**init_words(char *str, t_mshell *mshell);
//Expand
char	*expand(char *str, t_mshell *mshell);
//Get_env
char	*get_env(char *str, char **envir);
//Errors
void	error_cmd_not_found(char *cmd);
int		error_cd(char *cmd);
int find_char_echo(char *str, char c);

#endif // MINISHELL_H
