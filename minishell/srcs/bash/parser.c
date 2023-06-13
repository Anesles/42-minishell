/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/13 21:08:52 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	check_commands(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

void	wait_forks(t_mshell *mshell, pid_t pid, int *status)
{
	close(mshell->fd[0]);
	close(mshell->fd[1]);
	waitpid(pid, status, 0);
}

void	multiple_cmds(t_mshell *mshell, t_cmds *cmds)
{
	int		i;
	pid_t	pid;
	int		status;

	i = -1;
	status = 0;
	while (++i < mshell->n_cmds)
	{
		mshell->current_cmd++;
		if (check_commands(cmds[i].words[0]))
			g_exit_status = cmds[i].built(&cmds[i], mshell);
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
	wait_forks(mshell, pid, &status);
	g_exit_status = WEXITSTATUS(status);
}

void	parser(t_cmds *cmds, t_mshell *mshell)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (mshell->n_cmds > 1)
		multiple_cmds(mshell, cmds);
	else
	{
		if (is_builtins(cmds->words[0]))
			g_exit_status = cmds->built(cmds, mshell);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				cmds[0].built(&cmds[0], mshell);
				exit(0);
			}
			else
				waitpid(pid, &status, 0);
			g_exit_status = WEXITSTATUS(status);
		}
		mshell->current_cmd++;
	}
}
