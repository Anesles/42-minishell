/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:37 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_words(char **words)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strdup("");
	while (words[i])
	{
		if (i == 0)
			str = ft_strjoin(temp, words[i]);
		else
			str = ft_strjoin(str, words[i]);
		free(words[i]);
		if (words[i + 1])
			str = ft_strjoin(str, " ");
		i++;
	}
	free(words);
	free(temp);
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
	char 	*str;

	str = NULL;
	name = get_name(word);
	temp = get_env(name, mshell->envior);
	if (temp == NULL)
	{
		free(name);
		return (ft_strjoin(ft_substr(word, 0, find_char(word, '$')),
				ft_substr(word, find_char(word, '$')
					+ ft_strlen(name) + 1, ft_strlen(word))));
	}
	str = ft_strjoin("$", name);
	free(name);
	word = ft_replace_env(word, str, temp);
	free(str);
	return (word);
}

char	*expand_env(char *str, t_mshell *mshell)
{
	int		i;
	bool	inside_single;
	char	*temp;
	char	*ret;
	char	**words;

	words = ft_split(str, ' ');
	free(str);
	i = 0;
	inside_single = false;
	while (words[i])
	{
		if (find_char(words[i], '\'') != -1
			&& find_char(words[i] + find_char(words[i], '\'') + 1, '\'') != -1)
			inside_single = !inside_single;
		if (inside_single == true)
		{
			i++;
			continue ;
		}
		temp = change_word(words[i], mshell);
		free(words[i]);
		words[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	ret = join_words(words);
	return (ret);
}

char	*expand(char *str, t_mshell *mshell)
{
	if (ft_strchr(str, '$') != NULL)
		return (expand_env(str, mshell));
	else
		return (str);
}
