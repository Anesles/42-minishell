/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/24 19:14:18 by brumarti         ###   ########.fr       */
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

char **arraydup(char **old)
{
	char 	**new;
	int		i;

	i = 0;
	while(old[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	return (new);
}
int	main(int	argc, char *argv[], char **envp)
{
	char		*prompt;
	char		**words;
	t_mshell	*mshell;
	t_lexer		*lexer;
	t_cmds		*cmds;

	if (argc != 1 || argv[1])
		write(1, "cant't take inputs", 18);
	signal(SIGINT, sig_continue);
	signal(SIGQUIT, sig_quit);
	mshell = malloc(sizeof(t_mshell));
	mshell->envior = arraydup(envp);
	mshell->PATH = Get_PATH(mshell->envior);
	while (1)
	{
		pipe(mshell->fd);
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