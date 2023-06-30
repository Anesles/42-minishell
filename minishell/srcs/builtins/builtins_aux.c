/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinc_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:13:20 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/06/30 14:13:21 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	char			*t1;
	char			*t2;

	t1 = (char *)s1;
	t2 = (char *)s2;
	while (*t1 && *t2 && (*t1 == *t2))
	{
		t1++;
		t2++;
	}
	return ((int)(unsigned char)(*t1) - (int)(unsigned char)(*t2));
}

void	order_array(char **str)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	i = 0;
	j = 0;
	size = 0;
	while (str[size])
		size++;
	while (j < size - 1)
	{
		i = 0;
		while (i < size - j - 1)
		{
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				temp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

int	next_one(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

int	b_declare(t_mshell *mshell)
{
	int		i;
	char	**array;
	char	*str;
	int		j;

	array = arraydup(mshell->envior);
	order_array(array);
	i = 0;
	while (array[i])
	{
		j = 0;
		str = ft_substr(array[i], j, next_one(array[i], '='));
		ft_printf("declare -x %s=", str);
		free(str);
		j = j + next_one(array[i], '=') + 1;
		str = ft_substr(array[i], j, ft_strlen(array[i]));
		ft_printf("\"%s\"\n", str);
		free(array[i]);
		free(str);
		i++;
	}
	free(array);
	return (EXIT_SUCCESS);
}
