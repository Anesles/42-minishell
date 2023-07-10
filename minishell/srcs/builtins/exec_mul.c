/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:59:41 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/08 14:35:48 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	exec_child(t_mshell *mshell, t_cmds *cmds, int **pipefd, int i)
{
	handle_pipes(i, pipefd, mshell);
	if (is_builtins(cmds[i].words[0]))
		g_exit_status = cmds[i].built(&cmds[i], mshell);
	else
		cmds[i].built(&cmds[i], mshell);
	exit(g_exit_status);
}

void	end_exec(t_mshell *mshell, pid_t *pid, int **pipefd)
{
	int	i;
	int	status;

	i = mshell->n_cmds - 1;
	while (i >= 0)
	{
		if (i == mshell->n_cmds -1)
			waitpid(pid[i], &status, 0);
		else
			waitpid(pid[i], NULL, 0);
		if (i != 0)
		{
			close(pipefd[i - 1][READ]);
			close(pipefd[i - 1][WRITE]);
		}
		i--;
	}
	free(pid);
	i = 0;
	while (i < mshell->n_cmds - 1)
		free(pipefd[i++]);
	free(pipefd);
	if (!WTERMSIG(status))
		g_exit_status = WEXITSTATUS(status);
}

void	init_pipefd(int **pipefd, t_mshell *mshell, t_cmds *cmds)
{
	int		i;
	(void)cmds;
	i = -1;
	while (++i < mshell->n_cmds - 1)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		pipe(pipefd[i]);
	}
}

void	multiple_cmds(t_mshell *mshell, t_cmds *cmds)
{
	int		**pipefd;
	pid_t	*pid;
	int		i;

	sig_fork();
	pipefd = malloc(sizeof(int *) * mshell->n_cmds);
	pid = malloc(sizeof(pid_t) * mshell->n_cmds);
	init_pipefd(pipefd, mshell, cmds);
	i = -1;
	while (++i < mshell->n_cmds)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(EXIT_FAILURE);
		else if (pid[i] == 0)
			exec_child(mshell, cmds, pipefd, i);
		if (i < mshell->n_cmds - 1)
			close(pipefd[i][WRITE]);
		if (i > 0)
			close(pipefd[i - 1][READ]);
//		waitpid(pid[i], &status, WNOHANG);
	}
	end_exec(mshell, pid, pipefd);
}
/* 
void	multiple_cmds(t_mshell *mshell, t_cmds *cmds)
{
	int fdin;
	int tmpin;
	int tmpout;
	int	ret;
	int	fdout;
	int	i;
	int	fdpipe[2];

	tmpin = dup(0);
	tmpout = dup(1);
	fdin = dup(tmpin);
	i = 0;
	while(i < mshell->n_cmds)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == mshell->n_cmds -1)
		{
			fdout=dup(tmpout);
		}
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		ret = fork ();
		if (ret == 0)
		{
			if (is_builtins(cmds[i].words[0]))
				g_exit_status = cmds[i].built(&cmds[i], mshell);
			else
				cmds[i].built(&cmds[i], mshell);
			exit(g_exit_status);
		}
		dup2(tmpin, 0);
		dup2(tmpout, 1);

		i++;
	}
	close(tmpin);
	close(tmpout);

} */