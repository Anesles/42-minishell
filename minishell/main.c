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
		prompt = readline("minishell: ");
		words = ft_split(prompt, ' ');
		free(prompt);
		lexer = init_lexer(words, count_words(words));
		cmds = init_cmds(lexer, mshell);
		parser(cmds, mshell);
		free(lexer);
		free(cmds);
		clear_words(words, count_words(words));
	}
	return (1);
}