/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/16 18:16:36 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*chamada(void)
{
	char	*str;
	char		buff[256];
	str = getcwd(buff, sizeof(buff));
	str = ft_strjoin(str, "$ ");
	return (str);
}

void	sig_continue(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_quit(int signum)
{
	(void)signum;
	write(1, "\b\b  \b\b", 6	);
}

int	main(void)
{
	char		*prompt;
	char		**words;
	t_mshell	*mshell;
	t_lexer		*lexer;
	t_cmds		*cmds;

	signal(SIGINT, sig_continue);
	signal(SIGQUIT, sig_quit);
	while (1)
	{
		mshell = malloc(sizeof(mshell));
		prompt = chamada();
		prompt = readline(prompt);
		if (prompt == NULL)
			b_exit(0);
		if (ft_strlen(prompt) > 0)
			add_history(prompt);
		words = ft_split(prompt, ' ');
		if (!(words[0] == NULL))
		{
			free(prompt);
			lexer = init_lexer(words, count_words(words));
			cmds = init_cmds(lexer, mshell);
			parser(cmds, mshell);
			free(lexer);
			free(cmds);
		}
		clear_words(words, count_words(words));
	}
	return (1);
}