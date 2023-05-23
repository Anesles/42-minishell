/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/23 17:29:11 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_cmds *cmds, t_mshell *mshell)
{
	int		i;
	pid_t	pid[258];

	if (mshell->n_cmds > 1)
	{
		i = -1;
		while (++i < mshell->n_cmds)
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				cmds[i].built(cmds[i].words, cmds[i].count_words, mshell);
				mshell->current_cmd++;
				if (pid[i] == 0)
					exit(0);
			}
		}
	}
	else
	{
		pid[0] = fork();
		if (pid[0] == 0)
		{
			cmds[0].built(cmds[0].words, cmds[0].count_words, mshell);
			mshell->current_cmd++;
			if (pid[0] == 0)
					exit(0);
		}
	}
	i = -1;
	while (++i < mshell->n_cmds)
		waitpid(pid[i], NULL, 0);
}