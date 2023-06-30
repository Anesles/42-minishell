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

char	**start_loop(t_mshell *mshell)
{
	char		*prompt;
	char		**words;

	prompt = prompt_read(mshell);
	change_exit_st(mshell);
	words = init_words(prompt, mshell);
	free(prompt);
	return (words);
}

void	minishell_loop(t_mshell *mshell)
{
	char		**words;

	while (1)
	{
		pipe(mshell->fd);
		pipe(mshell->prev_fd);
		words = start_loop(mshell);
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
				b_export_one("?=2", mshell);
			}
		}
	}
}
