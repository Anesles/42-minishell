/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:51:28 by brumarti         ###   ########.fr       */
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

void	parser_aux(t_cmds *cmds, t_mshell *mshell, int pid)
{
	int	i;

	i = -1;
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
}

void	parser_aux_2(t_cmds *cmds, t_mshell *mshell, int pid, int status)
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

void	parser(t_cmds *cmds, t_mshell *mshell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = 0;
	if (mshell->n_cmds > 1)
	{
		parser_aux(cmds, mshell, pid);
		close(mshell->fd[0]);
		close(mshell->fd[1]);
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	else
		parser_aux_2(cmds, mshell, pid, status);
}
