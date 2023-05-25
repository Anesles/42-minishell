/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:55:39 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/25 01:25:44 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_expand(char	*word);
char	*get_values(char	*word);

void	create_lexer(t_lexer *lexer, char **words, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		lexer[i].word = check_expand(words[i]);
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

t_lexer	*init_lexer(char **words, int n)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer) * n);
	create_lexer(lexer, words, n);
	return (lexer);
}

char	*check_expand(char	*word)
{
/* 	char	**newword;
	char	*final; */
	char	*dollar;
/* 	int		i;
	int		tamanho;
	int 	final; */
	if (word[0] != '$')
		return (word);
	dollar = getenv(&word[1]);
	if (dollar == NULL)
		return (NULL);
	return (dollar);

/*	newword = ft_split(word, '$');
	i = 0;
	while(newword[i] != NULL)
		i++;
	if (i == 1)
		return(word)
	while(i > 1)
	{
		dollar = get_value(&word[i]);
		dollar = getenv(dollar);
		final = ft_strjoin(newword[i], dollar);
		i--;
	}
	return ()
 	tamanho = 1;
	final = 0;
	i = 0;
	while(word[i])
	{
		if (word[i] == '$')
		{
			dollar = get_values(&word[i + 1]);
			dollar = getenv(dollar);
			tamanho = ft_strlen(dollar);
			i++;
		}
		final += tamanho;
		tamanho = 1;
		i++;
	}
	i = 0; */

}

/* char	*check_expand_aux(char *old, int	i)
{

} */

char	*get_values(char	*word)
{
	char	*new;
	int	i;
	int	j;

	i = 0;
	while(word[i] || word[i] != ' ')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while(i > 0)
	{
		new[j] = word[i];
		i--;
		j++;
	}
	new[j] = '\0';
	return (new);
}
