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
	char	*str;
	int		i;

	cmd[0] = ft_strtrim(cmd[0], " \t");
	available = ft_split(mshell->path, ':');
	i = 0;
	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	else
	{
		while (available[i])
		{
			str = ft_strjoin(available[i], "/");
			str = ft_strjoin(str, cmd[0]);
			if (!access(str, X_OK))
				return (str);
			i++;
		}
	}
	return (NULL);
}

void	executables(char **cmd, t_mshell *mshell)
{
	char	*bin;

	bin = returnvalue(cmd, mshell);
	if (bin == NULL)
		bin = "none";
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
			break ;
		i++;
	}
	return (ft_substr(pwd[i], 5, ft_strlen(pwd[i]) - 5));
}
