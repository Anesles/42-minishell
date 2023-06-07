/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 14:54:17 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str, char **envir)
{
	int		i;

	i = 0;
	while (envir[i])
	{
		if (ft_strncmp(str, envir[i], ft_strlen(str)) == 0)
			return (envir[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}

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
		while(ft_isalnum(str[i++]))
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

char	*expand_env(char *str, t_mshell *mshell)
{
	int		i;
	char	*name;
	char	*temp;
	char	**words;

	words = ft_split(str, ' ');
	i = 0;
	if (count_words(words) == 1)
	{
		while (find_char(words[0], '$') != -1)
		{
			name = get_name(words[0]);
			temp = get_env(name, mshell->envior);
			if (temp == NULL)
				break ;
			words[0] = ft_replace_env(words[0], ft_strjoin("$", name), temp);
		}
	}
	else
	{
		while (words[i])
		{
			while (find_char(words[i], '$') != -1)
			{
				while (1)
				{
					name = get_name(words[i]);
					temp = get_env(name, mshell->envior);
					if (temp == NULL)
						break;
				}
				words[i] = ft_replace_env(words[i], ft_strjoin("$", name), temp);
			}
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