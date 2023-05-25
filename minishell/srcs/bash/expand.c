/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/25 18:54:48 by brumarti         ###   ########.fr       */
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
	return (ft_strdup(""));
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
	char	**words;

	i = 0;
	words = ft_split(str, ' ');
	if (count_words(words) == 1)
	{
		if (ft_strchr(words[0], '$') != NULL)
			words[0] = get_env(ft_strtrim(words[0], "$"), mshell->envior);
		else
			return (words[0]);
	}
	else
	{
		while (words[i])
		{
			if (ft_strchr(words[i], '$') != NULL)
				words[i] = get_env(ft_strtrim(words[i], "$"), mshell->envior);
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