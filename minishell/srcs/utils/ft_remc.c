/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:10 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:35:22 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_chars(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*loop(char *str, char c, char *temp, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (str[j] == c)
		{
			j++;
			continue ;
		}
		temp[i] = str[j];
		j++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_remc(char *str, char c)
{
	int		size;
	char	*temp;
	int		count;

	count = count_chars(str, c);
	size = ft_strlen(str) - count + 1;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp = loop(str, c, temp, size);
	return (temp);
}
