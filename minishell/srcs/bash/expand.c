/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/06 17:53:59 by brumarti         ###   ########.fr       */
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

char	*expand_env(char *str, t_mshell *mshell)
{
	int		i;
	int		j;
	char	*name;
	char	*temp;
	char	**words;

	words = ft_split(str, ' ');
	i = 0;
	if (count_words(words) == 1)
	{
		while (find_char(words[0], '$') != -1)
		{
			i = 0;
			while (1)
			{
				name = ft_substr(words[0], find_char(words[0], '$') + 1, 1 + i);
				temp = get_env(name, mshell->envior);
				if (temp != NULL && find_char(temp, '=') == -1)
					break;
				i++;
			}
			words[0] = ft_replace_env(words[0], ft_strjoin("$", name), temp);
		}
	}
	else
	{
		while (words[i])
		{
			while (find_char(words[i], '$') != -1)
			{
				j = 0;
				while (1)
				{
					name = ft_substr(words[i], find_char(words[i], '$') + 1, 1 + j);
					temp = get_env(name, mshell->envior);
					if (temp != NULL && find_char(temp, '=') == -1)
						break;
					j++;
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