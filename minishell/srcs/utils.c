/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:22:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/06 17:18:48 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

void	clear_words(char **words, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		free(words[i]);
	free(words);
}

int	find_char(char *str, char c)
{
	size_t	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (i == ft_strlen(str) && c != 0)
		return (-1);
	else
		return (i);
}

int	is_redir(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (1);
	else if (!ft_strncmp(str, "<<", 2))
		return (1);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

int	is_builtins(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (1);
	return (0);
}

char *ft_replace_env(const char* str, const char *substr, const char *replace)
{
	int	i;
	size_t	j;
	int	start;
	int	flag;
	char *output;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == substr[j]) 
		{
			if (!flag)
					start = i;
			j++;
			if (substr[j] == '\0')
					break;
			flag = 1;
		} 
		else 
		{
			flag = 0;
			start = 0;
			j = 0;
		}
		i++;
	}
	output = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(substr) + ft_strlen(replace)));
	if (substr[j] == '\0' && flag)
	{
		i = -1;
		while (++i < start)
			output[i] = str[i];

		j = -1;
		while (++j < ft_strlen(replace))
		{
			output[i] = replace[j];
			i++;
		}
	
		j = start + ft_strlen(substr) - 1;
		while (++j < ft_strlen(str))
		{
				output[i] = str[j];
				i++;
		}
		output[i] = '\0';
	} 
	else 
	{
		ft_printf("%s is not a substring of %s\n", substr, str);
		return (NULL);
	}
	return(output);
}