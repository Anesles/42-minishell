/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:55:39 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/13 16:12:42 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lexer(t_lexer *lexer, char **words, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		lexer[i].word = words[i];
		if (lexer[i].word == NULL)
			lexer[i].word = " ";
		if (i != 0)
			lexer[i].prev = &lexer[i - 1];
		else
			lexer[i].prev = NULL;
		if (i != n - 1)
			lexer[i].next = &lexer[i + 1];
		else
			lexer[i].next = NULL;
		i++;
	}
}

void	expand_lexer(t_lexer *lexer, t_mshell *mshell, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		lexer[i].word = expand(lexer[i].word, mshell);
		lexer[i].word = ft_strtrim(lexer[i].word, "\'\"");
		i++;
	}
}

t_lexer	*init_lexer(char **words, int n, t_mshell *mshell)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer) * n);
	create_lexer(lexer, words, n);
	expand_lexer(lexer, mshell,n);
	return (lexer);
}
