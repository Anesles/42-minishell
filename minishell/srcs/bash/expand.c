/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/13 17:10:59 by brumarti         ###   ########.fr       */
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

	name = get_name(word);
	ft_printf("name:%s\n", name);
	temp = get_env(name, mshell->envior);
	if (temp == NULL)
		return (ft_strjoin(ft_substr(word, 0, find_char(word, '$')),
			ft_substr(word, find_char(word, '$') + ft_strlen(name) + 1, ft_strlen(word))));
	word = ft_replace_env(word, ft_strjoin("$", name), temp);
	return (word);
}

char	*expand_env(char *str, t_mshell *mshell)
{
	int		i;
	bool	inside_single;
	char	**words;

	words = ft_split(str, ' ');
	i = 0;
	inside_single = false;
	while (words[i])
	{
		if (find_char(words[i], '\'') != -1 && find_char(words[i] + find_char(words[i], '\'') + 1, '\'') != -1)
			inside_single = !inside_single;
		if (inside_single == true)
		{
			i++;
			continue ;
		}
		words[i] = change_word(words[i], mshell);
		i++;
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
