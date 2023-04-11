/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/11 16:12:50 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main()
{
	while (1)
	{
		int	n;
		char *prompt;
		char **words;
		t_lexer **lexer;
		
		prompt = readline("minishell: ");
		words = ft_split(prompt, ' ');
		free(prompt);
		n = count_words(words);
		lexer = (t_lexer **)malloc(sizeof(t_lexer *) * n);
		init_lexer(lexer, words);
		clear_lexer(lexer, n);
		clear_words(words, n);
	}
	return (1);
}