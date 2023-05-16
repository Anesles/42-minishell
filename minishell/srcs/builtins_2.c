/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/16 16:29:32 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_ls(t_mshell *mshell)
{
	struct dirent *entry;
	DIR *dir;

	if (mshell->current_cmd == mshell->n_cmds - 1)
	{
		dir = opendir(".");
		if (dir == NULL)
			send_error("opendir");
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (!ft_strncmp(".", entry->d_name, ft_strlen(".")))
				entry = readdir(dir);
			else
			{
				if(mshell->current_cmd == mshell->n_cmds - 1)
					ft_putstr_fd(ft_strjoin(entry->d_name, "\n"), STDOUT_FILENO);
				else
					ft_putstr_fd(ft_strjoin(entry->d_name, "\n"), mshell->fd[0]);
				entry = readdir(dir);
			}
		}
	}
}

void	b_exec(char *cmd, char **words)
{
	execve(cmd, words, words);
}
