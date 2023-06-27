/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:55:39 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 18:08:32 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lexer(t_lexer *lexer, char **words, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		lexer[i].word = ft_strdup(words[i]);//TODO, NAO PODEMOS ACEDECER ASSIM, TEMOS DE FAZER UM STRDUP
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
	int		i;
	char 	*str;

	i = 0;
	while (i < n)
	{
		str = expand(lexer[i].word, mshell);
		str = ft_remc(str, '\'');
		str = ft_remc(str, '"');
		lexer[i].word = ft_strdup(str);
		free(str);
		str = NULL;
		i++;
	}
}

t_lexer	*init_lexer(char **words, int n, t_mshell *mshell)
{
	t_lexer	*lexer;
	int		i;

	lexer = (t_lexer *)malloc(sizeof(t_lexer) * n);
	create_lexer(lexer, words, n);
	expand_lexer(lexer, mshell, n);
	i = -1;
	while(++i < n)
			free(words[i]);
	free(words);
	return (lexer);
}
