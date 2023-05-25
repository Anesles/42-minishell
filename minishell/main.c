/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/25 17:52:00 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int g_exit_status = 0;

char	*chamada(void)
{
	char	*str;
	char	buff[256];

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

char	**arraydup(char **old)
{
	char	**new;
	int		i;

	i = 0;
	while (old[i])
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

int	main(int argc, char *argv[], char **envp)
{
	char		*prompt;
	char		**words;
	t_mshell	mshell;
	t_lexer		*lexer;
	t_cmds		*cmds;

	if (argc != 1 || argv[1])
		perror("minishell: too many arguments");
	signal(SIGINT, sig_continue);
	signal(SIGQUIT, sig_quit);
	mshell.envior = arraydup(envp);
	mshell.PATH = get_path(mshell.envior);
	while (1)
	{
		pipe(mshell.fd);
		prompt = chamada();
		prompt = readline(prompt);
		if (prompt == NULL)
			b_exit(0);
		if (ft_strlen(prompt) > 0)
			add_history(prompt);
		words = init_words(prompt, &mshell);
		if (words == NULL)
			continue ;
		if (!(words[0] == NULL))
		{
			free(prompt);
			lexer = init_lexer(words, count_words(words));
			cmds = init_cmds(lexer, &mshell);
			parser(cmds, &mshell);
			free(lexer);
			free(cmds);
		}
		clear_words(words, count_words(words));
	}
	return (1);
}
