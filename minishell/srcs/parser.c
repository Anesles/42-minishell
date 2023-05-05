/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/05 15:48:22 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_cmds *cmds, t_mshell *mshell)
{
	int		i;
	pid_t	pid[258];

	if (mshell->n_cmds > 1)
	{
		pipe(mshell->fd);
		i = -1;
		while (++i < mshell->n_cmds)
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				if (i == mshell->n_cmds)
					cmds[i].built(cmds[i].words, cmds[i].count_words, mshell);
				else
					cmds[i].built(cmds[i].words, cmds[i].count_words, mshell);
				exit(0);
			}
			mshell->current_cmd++;
		}
		i = -1;
		while (++i < mshell->n_cmds)
			waitpid(pid[i], NULL, 0);
	}
	else
		cmds[0].built(cmds[0].words, cmds[0].count_words, mshell);
}