/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/05 15:28:28 by brumarti         ###   ########.fr       */
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
int	main(void)
{
	char		*prompt;
	char		**words;
	t_mshell	*mshell;
	t_lexer		*lexer;
	t_cmds		*cmds;

	while (1)
	{
		mshell = malloc(sizeof(mshell));
		prompt = chamada();
		prompt = readline(prompt);
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