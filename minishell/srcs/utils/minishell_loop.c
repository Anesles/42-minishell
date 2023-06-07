/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:36:40 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 16:08:43 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	int g_exit_status;

char	*chamada(void)
{
	char	*str;
	char	buff[256];

	str = getcwd(buff, sizeof(buff));
	str = ft_strjoin(str, "$ ");
	return (str);
}

char	*prompt_read(void)
{
	char	*prompt;

	prompt = chamada();
	prompt = readline(prompt);
	if (prompt == NULL)
	{
		write (1, "exit\n", 5);
		b_exit(1);
	}
	if (ft_strlen(prompt) > 0)
		add_history(prompt);
	return (prompt);
}

void	clear_mem(t_mshell *mshell, t_lexer *lexer, t_cmds *cmds)
{
	unlink("temp");
	reset_pipes(mshell);
	free(lexer);
	free(cmds);
}

void	minishell_loop(t_mshell *mshell)
{
	char		*prompt;
	char		**words;
	t_lexer		*lexer;
	t_cmds		*cmds;

	while (1)
	{
		pipe(mshell->fd);
		prompt = prompt_read();
		words = init_words(prompt, mshell);
		if (words == NULL)
			continue ;
		if (!(words[0] == NULL))
		{
			free(prompt);
			lexer = init_lexer(words, count_words(words));
			cmds = init_cmds(lexer, mshell);
			parser(cmds, mshell);
			b_export(ft_strjoin("?=", ft_itoa(g_exit_status)), mshell);
			clear_mem(mshell, lexer, cmds);
		}
		clear_words(words, count_words(words));
	}
}