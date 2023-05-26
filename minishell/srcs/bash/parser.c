/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/25 15:42:41 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_commands(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	else
		return (0);
}

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
			if (check_commands(cmds[i].words[0]))
				cmds[i].built(&cmds[i], mshell);
			else
			{
				pid = fork();
				if (pid == 0)
				{
					handle_pipe(mshell);
					cmds[i].built(&cmds[i], mshell);
					exit(0);
				}
			}

		}
		close(mshell->fd[0]);
		close(mshell->fd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		mshell->current_cmd++;
		if (check_commands(cmds[0].words[0]))
			cmds[0].built(cmds, mshell);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				handle_pipe(mshell);
				cmds[0].built(cmds, mshell);
				exit(0);
			}
			close(mshell->fd[0]);
			close(mshell->fd[1]);
			waitpid(pid, NULL, 0);
		}
	}
}