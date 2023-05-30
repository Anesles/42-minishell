/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:02:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/30 16:22:48 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_words(char *str)
{
	bool insidequotes;
	bool insideword;
	int	count;
	int	i;

	count = 0;
	i = 0;
	insidequotes = false;
	insideword = false;
	while (str[i])
	{
		if (str[i] == '"')
		{
			insidequotes = !insidequotes;
		}
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

char	*get_words(char *str, t_mshell *mshell)
{
	if (*str == '"')//problema: no segundo "
	{
		str++;
		return (expand(ft_substr(str, 0, find_char(str, '"')) , mshell));
	}
	else if (*str == '\'')
	{
		str++;
		if (ft_strchr(str, '\'') == NULL)
			return (ft_substr(str, 0, find_char(str, ' ')));
		else
			return (ft_substr(str, 0, find_char(str, '\'')));
	}
	else
	{
		return (expand(ft_substr(str, 0, find_char(str, ' ')), mshell));
	}
}

char	**init_words(char *str, t_mshell *mshell)
{
	int		i;
	int		start;
	int		count;
	char	**words;

	if (ft_isprint(str[0]) == 0)
		return (NULL);
	count = number_words(str);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	start = 0;
	while (i < count)
	{
		words[i] = get_words(str + start, mshell);
		if (ft_strlen(words[i]) == 0)
			start += find_char(str + start, ' ');
		start += ft_strlen(words[i]) + 1;
		if (((*(str + start) == '"') || (*(str + start) == 39)) && (*(str + start + 1) == ' '))
			start += 2;
		i++;
	}
	words[i] = NULL;
	return (words);
}