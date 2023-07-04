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

int	nalloc_words(char *str)
{
	int		i;
	char	c;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i] == ' ' || str[i] == '\t')
		{
			count++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			i--;
		}
		else if (str[i] == '<' || str[i] == '>'
				|| str[i] == '|')
		{
			count++;
			i++;
			if ((str[i] == '<' || str[i] == '>') && str[i] == str[i - 1])
				i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			i--;
		}
		i++;
	}
	if (str[i - 1] == ' ' || str[i - 1] == '\t')
		return (count);
	return (count + 1);
}

char	**init_words(char	*str)
{
	int		i;
	int		j;
	int		start;
	int		count;
	char	**words;

	if (str[0] == '\0')
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (NULL);
	count = nalloc_words(str);
	words = malloc(sizeof(char *) * (count + 1));
	j = 0;
	i = 0;
	while (j < count)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i;
			i++;
			while (str[i] && str[i] != str[start])
				i++;
			if (str[i + 1] && (str[i + 1] != ' ' && str[i + 1] != '\t'))
			{
				while (str[i] && (str[i] != ' ' && str[i] != '\t'))
					i++;
				if (str[i] && (str[i] == ' ' || str[i] == '\t'))
					i--;
				words[j] = ft_substr(str, start, i - start + 1);
			}
			else
			{
				words[j] = ft_substr(str, start, i - start + 1);
				i++;
				while (str[i] && (str[i] == ' ' || str[i] == '\t'))
					i++;
				i--;
			}
			j++;
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if ((str[i] == '<' || str[i] == '>') && str[i + 1] == str[i])
			{
				words[j] = ft_substr(str, i, 2);
				i++;
			}
			else
				words[j] = ft_substr(str, i, 1);
			j++;
		}
		else
		{
			while ((str[i] == ' ' || str[i] == '\t') && str[i])
				i++;
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '<' && str[i] != '>'
				&& str[i] != '|')
				i++;
			words[j] = ft_substr(str, start, i - start);
			j++;
		}
		i++;
	}
	words[j] = NULL;
	return (words);
}
