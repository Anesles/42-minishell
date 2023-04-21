/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/21 17:54:38 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser(t_cmds *cmds, t_mshell *mshell)
{
	int	i;
	int	fd[2];
	
	if (mshell->n_cmds > 1)
	{
		pipe(fd);
		i = -1;	
		while (++i < mshell->n_cmds)
		{
			if (fork() == 0)
			{
				cmds[i].built(cmds[i].words, cmds[i].count_words);
				exit(0);
			}
		}	
	}
	else
		cmds[0].built(cmds[0].words, cmds[0].count_words);
}