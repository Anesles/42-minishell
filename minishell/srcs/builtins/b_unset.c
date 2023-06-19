/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:32:51 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/13 17:26:10 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(char *variable, t_mshell *mshell)
{
	int		count;
	int		track;
	char	**new_environ;

	if (!variable)
		return (EXIT_SUCCESS);
	count = 0;
	while (mshell->envior[count] != NULL)
		count++;
	new_environ = (char **)malloc(sizeof(char *) * count);
	count = 0;
	track = 0;
	while (mshell->envior[count] != NULL)
	{
		if (ft_strncmp(variable, mshell->envior[count], ft_strlen(variable)))
		{
			new_environ[track] = ft_strdup(mshell->envior[count]);
			track++;
		}
		count++;
	}
	new_environ[track] = NULL;
	mshell->envior = new_environ;
	return (EXIT_SUCCESS);
}
