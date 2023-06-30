/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:44:28 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:44:38 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str, char **envir)
{
	int		i;
	char	*temp;

	i = 0;
	while (envir[i])
	{
		temp = ft_strjoin(str, "=");
		if (ft_strncmp(temp, envir[i], ft_strlen(str) + 1) == 0)
		{
			free(temp);
			return (envir[i] + ft_strlen(str) + 1);
		}
		free(temp);
		i++;
	}
	return (NULL);
}
