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

int	var_exists(char *var, t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->envior[i] != NULL)
	{
		if (ft_strncmp(var, mshell->envior[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	b_unset(char **variable, t_mshell *mshell)
{
	int		count;
	int		track;
	char	**new_environ;

	int i = 1;
	while (variable[i])
	{
		if (!var_exists(variable[i], mshell))
		{
			i++;
			continue ;
		}
		else
		{
			count = 0;
			while (mshell->envior[count] != NULL)
				count++;
			new_environ = (char **)malloc(sizeof(char *) * count);
			count = 0;
			track = 0;
			while (mshell->envior[count] != NULL)
			{
				if (ft_strncmp(variable[i], mshell->envior[count], ft_strlen(variable[i])))
				{
					new_environ[track] = ft_strdup(mshell->envior[count]);
					track++;
				}
				count++;
			}
			new_environ[track] = NULL;
			free_envior(mshell);
			mshell->envior = arraydup(new_environ);
			free_array(new_environ);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
