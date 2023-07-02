/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:59:41 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/02 21:36:46 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_status;

void	sig_cont_child(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	g_exit_status = 130;
	exit(130);
}

void	exec_child(t_mshell *mshell, t_cmds *cmds, int (*pipefd)[2], int i)
{
	signal(SIGINT, &sig_cont_child);
	if (i == 0)
	{
		dup2(pipefd[i][1], STDOUT_FILENO);
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	else if (i == mshell->n_cmds - 1)
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		close(pipefd[i - 1][1]);
		close(pipefd[i - 1][0]);
	}
	else
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
		close(pipefd[i - 1][1]);
		close(pipefd[i - 1][0]);
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	if (is_builtins(cmds[i].words[0]))
		g_exit_status = cmds[i].built(&cmds[i], mshell);
	else
		cmds[i].built(&cmds[i], mshell);
	exit(g_exit_status);
}

void	multiple_cmds(t_mshell *mshell, t_cmds *cmds)
{
	int		(*pipefd)[2];
	int		status;
	pid_t	*pid;
	int		i;

	pipefd = malloc(sizeof(int [mshell->n_cmds - 1][2]));
	pid = malloc(sizeof(pid_t) * mshell->n_cmds);
	i = -1;
	while (++i < mshell->n_cmds - 1)
		pipe(pipefd[i]);
	i = -1;
	while (++i < mshell->n_cmds)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(EXIT_FAILURE);
		else if (pid[i] == 0)
			exec_child(mshell, cmds, pipefd, i);
	}
	i = -1;
	while (++i < mshell->n_cmds - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	i = -1;
	while (++i < mshell->n_cmds)
	{
		ft_printf("waiting for pid number: %d\n", i);
		waitpid(pid[i], &status, 0);
	}
	free(pid);
	free(pipefd);
	if (!WTERMSIG(status))
		g_exit_status = WEXITSTATUS(status);
}
