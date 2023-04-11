/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:55:39 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/11 16:08:31 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lexer(t_lexer **lexer, char **words, int n)
{
	int	i;

	i = 0;
	while(i < n)
	{
		lexer[i]->word = words[i];
		if (i != 0)
			lexer[i]->prev = lexer[i - 1];
		else
			lexer[i]->prev = NULL;
		if (i != n - 1)
			lexer[i]->next = lexer[i + 1];
		else
			lexer[i]->next = NULL;
		i++;
	}
}

void	alloc_lexer(t_lexer **lexer, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		lexer[i] = malloc(sizeof(t_lexer));
}

void	init_lexer(t_lexer **lexer, char **words)
{
	int	n;

	n = count_words(words);
	alloc_lexer(lexer, n);
	create_lexer(lexer, words, n);
}

void	clear_lexer(t_lexer **lexer, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		free(lexer[i]);
	free(lexer);
}