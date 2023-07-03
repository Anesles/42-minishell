/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 18:08:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ 0
# define WRITE 1
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
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
	int		n_cmds;
	int		current_cmd;
	char	**envior;
	int		i;
	int		j;
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
size_t	count_words(char **words);
void	change_exit_st(t_mshell *mshell);
int		find_char(char *str, char c);
int		is_redir(char *str);
int		is_builtins(char *str);
char	*ft_replace_env(char *str, char *substr, char *replace);
int		valid_nvar(char **nvar);
int		valid_nvar_one(char *nvar);
//Minishell_loop
void	minishell_loop(t_mshell *mshell);
int		valid_words(char **words);
//Lexer
t_lexer	*init_lexer(char **words, int n, t_mshell *mshell);
//Cmds
t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell);
int		builtins(t_cmds *cmds, t_mshell *mshell);
//Parser
void	parser(t_cmds *cmds, t_mshell *mshell);
//Builtins
void	b_exit(int status, t_mshell *mshell);
int		b_env(t_mshell *mshell);
void	order_array(char **str);
int		next_one(char *s, char c);
//Exc_mul
void	multiple_cmds(t_mshell *mshell, t_cmds *cmds);
//B_unset
int		b_unset(char *variable, t_mshell *mshell);
//B_export
void	handle_neq(char *n_var, t_mshell *mshell);
int		b_export(char **n_var, t_mshell *mshell);
int		b_declare(t_mshell *mshell);
int		b_export_one(char *n_var, t_mshell *mshell);
//B_echo
int		b_echo(char **words, int max_words);
//B_cd
int		b_cd(char *direct, t_mshell *mshell);
//Executables
char	**arraydup(char **old);
void	executables(char **cmd, t_mshell *mshell);
//Pipe
void	token_less(t_cmds *cmds, int mode);
void	token_more(t_cmds *cmds, int mode);
//Words
char	**init_words(char *str, t_mshell *mshell);
//Expand
char	*get_name(char *str);
char	*expand(char *str, t_mshell *mshell);
//Expand_env
char	*expand_env(char *str, t_mshell *mshell);
//Get_nsize
int		get_nsize(char *str, t_mshell *mshell);
//Get_env
char	*get_env(char *str, char **envir);
//Errors
int		error_cmd_not_found(char *cmd);
int		error_cd(char *cmd);
//Alloc_words
char	**alloc_words(t_lexer *lexer, t_cmds *cmds);
//Clear_mem
void	clear_mem(t_mshell *mshell, t_cmds *cmds);
void	free_lexer(t_lexer *lexer, int count);
void	free_envior(t_mshell *mshell);

#endif // MINISHELL_H
