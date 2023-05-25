/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/25 16:11:56 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*returnvalue(char **cmd, t_mshell *mshell)
{
	char	**available;
	char	*str;
	int		i;

	available = ft_split(mshell->PATH, ':');
	i = 0;
	while (available[i])
	{
		str = ft_strjoin(available[i], "/");
		str = ft_strjoin(str, cmd[0]);
		if (!access(str, X_OK))
			return (str);
		i++;
	}
	return (NULL);
}

void	executables(char **cmd, t_mshell *mshell)
{
	char	*bin;

	bin = returnvalue(cmd, mshell);
	execve(bin, cmd, mshell->envior);
}

char	*get_path(char **pwd)
{
	int		i;
	char	**str;

	i = 0;
	if (!pwd)
		return (NULL);
	while (pwd[i])
	{
		if (!ft_strncmp(pwd[i], "PATH", 4))
			break ;
		i++;
	}
	str = ft_split(pwd[i], '=');
	return (str[1]);
}