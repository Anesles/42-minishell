/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:02:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:51 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_words_quotes(char *str, int *i, int *j, char **words)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != str[start])
		(*i)++;
	if (str[*i + 1] && (str[*i + 1] != ' ' && str[*i + 1] != '\t'))
	{
		while (str[*i] && (str[*i] != ' ' && str[*i] != '\t'))
			(*i)++;
		if (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)--;
		words[*j] = ft_substr(str, start, *i - start + 1);
	}
	else
	{
		words[*j] = ft_substr(str, start, *i - start + 1);
		(*i)++;
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
		(*i)--;
	}
	(*j)++;
}

void	init_words_special_chars(char *str, int *i, int *j, char **words)
{
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		words[*j] = ft_substr(str, *i, 2);
		(*i)++;
	}
	else
		words[*j] = ft_substr(str, *i, 1);
	(*j)++;
}

void	init_words_word(char *str, int *i, int *j, char **words)
{
	int		start;

	while ((str[*i] == ' ' || str[*i] == '\t') && str[*i])
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '|')
		(*i)++;
	words[*j] = ft_substr(str, start, *i - start);
	if (str[*i] && (str[*i] == '<' || str[*i] == '>' || str[*i] == '|'))
		(*i)--;
	(*j)++;
}

void	init_words_loop(char *str, char **words, int count)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j < count)
	{
		while (is_space(str[i]))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			init_words_quotes(str, &i, &j, words);
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			init_words_special_chars(str, &i, &j, words);
		else
			init_words_word(str, &i, &j, words);
		i++;
	}
	words[j] = NULL;
}

char	**init_words(char	*str)
{
	int		count;
	char	**words;

	if (str[0] == '\0')
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (NULL);
	count = nalloc_words(str);
	if (count == -1)
	{
		ft_printf("minishell: syntax error unclosed\n");
		return (NULL);
	}
	ft_printf("count:%d\n", count);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	init_words_loop(str, words, count);
	if (!ft_strncmp(words[--count], "|", 1))
	{
		ft_printf("minishell: syntax error near unexpected token '|'\n");
		return (NULL);
	}
	return (words);
}
