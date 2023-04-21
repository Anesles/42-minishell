/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/12 17:58:59 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
/* 	while (1)
	{
		int	n;
		char *prompt;
		char **words;
		t_lexer **lexer;
		t_cmds **cmds;
		
		prompt = readline("minishell: ");
		words = ft_split(prompt, ' ');
		free(prompt);
		n = count_words(words);
		lexer = (t_lexer **)malloc(sizeof(t_lexer *) * n);
		init_lexer(lexer, words);
		cmds = init_cmds(lexer);
		clear_lexer(lexer, n);
		clear_words(words, n);
	} */
//	builtins("echo");
//	b_echo(&argv[1], argc);
	b_pwd();
	return (1);
}