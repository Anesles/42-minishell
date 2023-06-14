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

void	clear_mem(t_mshell *mshell, t_lexer *lexer, t_cmds *cmds)
{
	int	i;

	i = 0;
	while (lexer[i].next != NULL)
	{
		free(lexer[i].word);
		i++;
	}
	unlink("temp");
	reset_pipes(mshell);
	free(cmds);
}

int	minishell_loopit(char **words, t_mshell *mshell)
{
	t_cmds		*cmds;
	t_lexer		*lexer;

	lexer = init_lexer(words, count_words(words), mshell);
	cmds = init_cmds(lexer, mshell);
	if (cmds == NULL)
	{
		b_export(ft_strjoin("?=", ft_itoa(g_exit_status)), mshell);
		return (1);
	}
	parser(cmds, mshell);
	b_export(ft_strjoin("?=", ft_itoa(g_exit_status)), mshell);
	clear_mem(mshell, lexer, cmds);
	return (0);
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
		words = init_words(prompt, mshell);
		free(prompt);
		if (words == NULL)
			continue ;
		if (!(words[0] == NULL))
		{
			if (minishell_loopit(words, mshell))
				continue ;
		}	
		clear_words(words, count_words(words));
	}
}
