/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/24 18:17:50 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_cmds *cmds, t_mshell *mshell)
{
	int		i;
	pid_t	pid;

	if (mshell->n_cmds > 1)
	{
		i = -1;
		while (++i < mshell->n_cmds)
		{
			mshell->current_cmd++;
			pid = fork();
			if (pid == 0)
			{
				handle_pipe(mshell);
				cmds[i].built(&cmds[i], mshell);
				exit(0);
			}
			else
				waitpid(pid, NULL, 0);
		}
	}
	else
	{
		mshell->current_cmd++;
		pid = fork();
		if (pid == 0)
		{
			handle_pipe(mshell);
			cmds[0].built(&cmds[0], mshell);
			exit(0);
		}
		else
			waitpid(pid, NULL, 0);
	}
}