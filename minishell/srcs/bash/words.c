/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:02:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:51:48 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_words_aux(char *str, t_mshell *mshell, char **words, int start);

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
		if (str[i] == '"')
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

char	*ft_substr_new(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;

	if (s == NULL)
		return (NULL);
	s_len = strlen(s);
	if (start >= s_len)
		return (strdup(""));
	substr_len = (len > s_len - start) ? len : s_len - start;
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (substr == NULL)
		return (NULL);
	strncpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

int	number_of_c(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while(str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

char	*get_words(char *str, int max, int current, t_mshell *mshell)
{
	int get_num;

	get_num = number_of_c(str, '"');
	if (*str == '"')
	{
		str++;
		return (expand(ft_substr_new(str, 0, find_char(str, '"')), mshell));
	}
	else if (*str == '\'')
	{
		str++;
		if (ft_strchr(str, '\'') == NULL)
			return (ft_substr_new(str, 0, find_char(str, ' ')));
		else
			return (ft_substr_new(str, 0, find_char(str, '\'')));
	}
	else if (current == max - 1)
		return (expand(ft_substr_new(str, 0, find_char(str, '\0')), mshell));
	else
		return (expand(ft_substr_new(str, 0, find_char(str, ' ')), mshell));
}

char	**init_words(char *str, t_mshell *mshell)
{
	int		i;
	int		start;
	int		count;
	char	**words;

	start = 0;
	while (*(str + start) >= 1 && *(str + start) <= 32)
		start++;
	count = number_words(str + start);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	i = -1;
	words = init_words_aux(str, mshell, words, start);
	return (words);
}

char	**init_words_aux(char *str, t_mshell *mshell, char **words, int start)
{
	int	i;
	int	count;

	count = number_words(str + start);
	i = -1;
	while (++i < count)
	{
		while (*(str + start) >= 1 && *(str + start) <= 32)
			start++;
		words[i] = get_words(str + start, count, i, mshell);
		if (i == count - 1)
			start += find_char(str + start, '\0');
		else
			start += find_char(str + start, ' ') + 1;
		if (((*(str + start) == '"') || (*(str + start) == 39))
			&& (*(str + start + 1) == ' '))
			start += 2;
	}
	words[i] = NULL;
	return (words);
}
