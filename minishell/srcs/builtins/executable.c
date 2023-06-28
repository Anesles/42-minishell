/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 17:47:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*returnvalue(char **cmd, t_mshell *mshell)
{
	char	**available;
	char	*fin;
	char	*temp;
	char	*str;
	int		i;

	temp = ft_strtrim(cmd[0], " \t");
	available = ft_split(get_path(mshell->envior), ':');
	if (available == NULL)
		return (NULL);
	i = 0;
	if (!access(temp, X_OK))
		return (temp);
	else
	{
		while (available[i])
		{
			str = ft_strjoin(available[i], "/");
			free(available[i]);
			fin = ft_strjoin(str, temp);
			free(str);
			if (!access(fin, X_OK))
			{
				while (available[++i])
					free(available[i]);
				free(available);
				free(temp);
				return (fin);
			}
			free(fin);
			i++;
		}
	}
	free(temp);
	free(available);
	return (NULL);
}

void	executables(char **cmd, t_mshell *mshell)
{
	char	*bin;

	bin = returnvalue(cmd, mshell);
	if (bin == NULL)
		return ;
	execve(bin, cmd, mshell->envior);
}

char	*get_path(char **pwd)
{
	int		i;

	i = 0;
	if (!pwd)
		return (NULL);
	while (pwd[i])
	{
		if (!ft_strncmp(pwd[i], "PATH=", 5))
			return (ft_substr(pwd[i], 5, ft_strlen(pwd[i]) - 5));
		i++;
	}
	return (NULL);
}
