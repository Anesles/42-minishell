/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:36:40 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 18:12:36 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*chamada(void)
{
	char	*str;
	char	buff[256];

	str = getcwd(buff, sizeof(buff));
	str = ft_strjoin(str, "$ ");
	return (str);
}

char	*prompt_read(t_mshell *mshell)
{
	char	*prompt;
	char	*line;

	prompt = chamada();
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
	{
		free(line);
		write (1, "exit\n", 5);
		b_exit(1, mshell);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

int	valid_words(char **words)
{
	int	i;

	i = 0;
	if (words[0] == NULL)
		return (0);
	else if (words[0][0] == '|')
		return (0);
	else if (words[0][0] == ';')
		return (0);
	else if (words[0][0] == '<')
		return (0);
	else if (words[0][0] == '>')
		return (0);
	else if (words[0][0] == '&')
		return (0);
	while (words[i])
	{
		if (words[i + 1] && (is_redir(words[i]) && is_redir(words[i + 1])))
			return (0);
		i++;
	}
	return (1);
}

void	minishell_loopit(char **words, t_mshell *mshell)
{
	t_cmds		*cmds;
	t_lexer		*lexer;
	size_t		count;

	count = count_words(words);
	lexer = init_lexer(words, count, mshell);
	cmds = init_cmds(lexer, mshell);
	free_lexer(lexer, count);
	if (cmds == NULL)
	{
		change_exit_st(mshell);
		clear_mem(mshell, cmds);
	}
	parser(cmds, mshell);
	change_exit_st(mshell);
	clear_mem(mshell, cmds);
}

void	minishell_loop(t_mshell *mshell)
{
	char		*prompt;
	char		**words;

	while (1)
	{
		pipe(mshell->fd);
		pipe(mshell->prev_fd);
		prompt = prompt_read(mshell);
		change_exit_st(mshell);
		words = init_words(prompt, mshell);
		free(prompt);
		if (words == NULL)
		{
			free(words);
			continue ;
		}
		if (!(words[0] == NULL))
		{
			if (valid_words(words))
				minishell_loopit(words, mshell);
			else
			{
				ft_printf("minishell: syntax error\n");
				b_export("?=2", mshell);
			}
		}
	}
}
