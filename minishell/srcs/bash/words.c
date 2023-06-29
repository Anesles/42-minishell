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

int	number_words(char *str)
{
	bool	insidequotes;
	bool	insideword;
	int		count;
	int		i;

	count = 0;
	i = 0;
	insidequotes = false;
	insideword = false;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			insidequotes = !insidequotes;
		else if (str[i] != ' ' || insidequotes)
			insideword = true;
		else if (insideword)
		{
			count++;
			insideword = false;
		}
		i++;
	}
	if (insideword)
		count++;
	return (count);
}

char	*get_words(char *str, int max, int current)
{
	if (current == max - 1)
		return (ft_substr(str, 0, find_char(str, '\0')));
	else
		return (ft_substr(str, 0, find_char(str, ' ')));
}

char	**init_words_aux(char *str, int start)
{
	int	i;
	int	count;
	char **temp_words;

	count = number_words(str + start);
	if (count == 0)
		return (NULL);
	i = -1;
	temp_words = malloc(sizeof(char *) * (count + 1));
	if (!temp_words)
		return (NULL);
	while (++i < count)
	{
		while (*(str + start) >= 1 && *(str + start) <= 32)
			start++;
		temp_words[i] = get_words(str + start, count, i);
		if (i == count - 1)
			start += find_char(str + start, '\0');
		else
			start += find_char(str + start, ' ') + 1;
		if (((*(str + start) == '"') || (*(str + start) == 39))
			&& (*(str + start + 1) == ' '))
			start += 2;
	}
	temp_words[i] = NULL;
	return (temp_words);
}

char	**init_words(char *str, t_mshell *mshell)
{
	int		start;
	char	**words;

	(void) mshell;
	start = 0;
	while (*(str + start) >= 1 && *(str + start) <= 32)
		start++;
	words = init_words_aux(str, start);
	if (words == NULL)
	{
		free(words);
		return (NULL);
	}
	return (words);
}
