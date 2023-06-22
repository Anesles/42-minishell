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

void	clear_cmds(t_cmds *cmds, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		free(cmds[i].words);
		i++;
	}
	free(cmds);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*current;
	t_lexer *next;
		
	current = lexer;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->word);
		current = next;
	}
	free(lexer);
}

void	clear_mem(t_mshell *mshell, t_cmds *cmds)
{
	clear_cmds(cmds, mshell->n_cmds);
	unlink("temp");
	reset_pipes(mshell);

}

int	minishell_loopit(char **words, t_mshell *mshell)
{
	t_cmds		*cmds;
	t_lexer		*lexer;
	char 		*status;
	char 		*str;
	size_t			count;

	count = count_words(words);
	ft_printf("count:%d\n", count);
	lexer = init_lexer(words, count, mshell);
	cmds = init_cmds(lexer, mshell);
	if (cmds == NULL)
	{
		status =  ft_itoa(g_exit_status);
		str = ft_strjoin("?=", status);
		free_lexer(lexer);
		b_export(str, mshell);
		clear_mem(mshell, cmds);
		free (status);
		free (str);
		return (1);
	}
	parser(cmds, mshell);
	status =  ft_itoa(g_exit_status);
	str = ft_strjoin("?=", status);
	b_export(str, mshell);
	free_lexer(lexer);
	clear_mem(mshell, cmds);
	free(status);
	free(str);
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
		
	}
}
