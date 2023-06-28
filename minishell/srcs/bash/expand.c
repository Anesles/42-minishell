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

int	get_nsize(char *str, t_mshell *mshell)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' && find_char(&str[i + 1], '\'') != -1)
		{
			i++;
			count++;
			while(str[i] != '\'')
			{
				count++;
				i++;
			}
		}
		if (str[i] == '$')
		{
			count += ft_strlen(get_env(get_name(str + i), mshell->envior));
			i++;
			while (ft_isalnum(str[i]) || str[i] == '?')
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*expand_env(char *str, t_mshell *mshell)
{
	char	*ret;
	int		j;
	int		i;

	ret = malloc(sizeof(char) * get_nsize(str, mshell) + 1);
	ft_printf("size: %d\n", get_nsize(str, mshell));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && find_char(&str[i + 1], '\'') != -1)
		{
			ret[j] = str[i];
			j++;
			i++;
			while (str[i] != '\'')
			{
				ret[j] = str[i];
				j++;
				i++;
			}
			ret[j] = str[i];
			j++;
			i++;
		}
		else if (str[i] == '$')
		{
			j += (int) ft_strlcat(ret, get_env(get_name(str + i), mshell->envior), get_nsize(str, mshell) + 1);
			i++;
			while (ft_isalnum(str[i]) || str[i] == '?')
				i++;
		}
		else
		{
			ret[j] = str[i];
			j++;
			i++;
		}
	}
	ret[get_nsize(str, mshell)] = 0;
	return (ret);
}

char	*expand(char *str, t_mshell *mshell)
{
	if (ft_strchr(str, '$') != NULL)
		return (expand_env(str, mshell));
	else
		return (str);
}
