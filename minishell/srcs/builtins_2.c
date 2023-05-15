/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/15 16:34:05 by brumarti         ###   ########.fr       */
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
		{
			printf("Error: opendir");
			return ;
		}
		
		entry = readdir(dir);
		while (entry != NULL)
		{
			printf("%s\n", entry->d_name);
			entry = readdir(dir);
		}
	}
}