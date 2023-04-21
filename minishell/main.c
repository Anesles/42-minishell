/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/21 17:44:31 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
 	while (1)
	{
		int	n;
		char *prompt;
		char **words;
		t_mshell *mshell;
		t_lexer *lexer;
		t_cmds *cmds;
		
		mshell = malloc(sizeof(mshell));
		prompt = readline("minishell: ");
		words = ft_split(prompt, ' ');
		free(prompt);
		n = count_words(words);
		lexer = init_lexer(words, n);
		cmds = init_cmds(lexer, mshell);
		parser(cmds, mshell);
		free(lexer);
		free(cmds);
		clear_words(words, n);
	}
	return (1);
}