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
		while (ft_isalnum(str[i]) || str[i] == '_')
		{
			count++;
			i++;
		}
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

char	*expand(char *str, t_mshell *mshell)
{
	if (ft_strchr(str, '$') != NULL)
		return (expand_env(str, mshell));
	else
		return (ft_strdup(str));
}
