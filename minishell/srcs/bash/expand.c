/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:48:39 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_words(char **words)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (words[i])
	{
		str = ft_strjoin(str, words[i]);
		if (words[i + 1])
			str = ft_strjoin(str, " ");
		i++;
	}
	return (str);
}

char	*get_name(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*name;

	count = 0;
	i = find_char(str, '$') + 1;
	if (str[i] == '?')
		count = 1;
	else
	{
		while (ft_isalnum(str[i++]))
			count++;
	}
	name = malloc(sizeof (char) * count + 1);
	if (!name)
		return (NULL);
	i = find_char(str, '$') + 1;
	j = 0;
	while (j < count)
		name[j++] = str[i++];
	name[j] = 0;
	return (name);
}

char	*change_word(char *word, t_mshell *mshell)
{
	char	*name;
	char	*temp;

	while (find_char(word, '$') != -1)
	{
		name = get_name(word);
		temp = get_env(name, mshell->envior);
		if (temp == NULL)
			break ;
		word = ft_replace_env(word, ft_strjoin("$", name), temp);
	}
	return (word);
}

char	*expand_env(char *str, t_mshell *mshell)
{
	int		i;
	char	**words;

	words = ft_split(str, ' ');
	i = 0;
	if (count_words(words) == 1)
		words[0] = change_word(words[0], mshell);
	else
	{
		while (words[i])
		{
			words[i] = change_word(words[i], mshell);
			i++;
		}
	}
	return (join_words(words));
}

char	*expand(char *str, t_mshell *mshell)
{
	if (ft_strchr(str, '$') != NULL)
		return (expand_env(str, mshell));
	else
		return (str);
}
