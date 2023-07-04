/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:59:41 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/04 16:55:50 by brumarti         ###   ########.fr       */
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
	check_redirect(cmds);
	if (i == 0)
	{
		if (cmds->token == NULL && cmds->token[0] != '>' && ft_strncmp(cmds->token, ">>", 2) != 0)
			dup2(pipefd[i][WRITE], STDOUT_FILENO);
		close(pipefd[i][READ]);
		close(pipefd[i][WRITE]);
	}
	else if (i == mshell->n_cmds - 1)
	{
		if (cmds->token == NULL && cmds->token[0] != '<' && ft_strncmp(cmds->token, "<<", 2) != 0)
			dup2(pipefd[i - 1][READ], STDIN_FILENO);
		close(pipefd[i - 1][READ]);
		close(pipefd[i - 1][WRITE]);
	}
	else
	{
		if (cmds->token == NULL && cmds->token[0] != '<' && ft_strncmp(cmds->token, "<<", 2) != 0)
			dup2(pipefd[i - 1][READ], STDIN_FILENO);
		if (cmds->token == NULL && cmds->token[0] != '>' && ft_strncmp(cmds->token, ">>", 2) != 0)
			dup2(pipefd[i][WRITE], STDOUT_FILENO);
		close(pipefd[i - 1][READ]);
		close(pipefd[i - 1][WRITE]);
		close(pipefd[i][READ]);
		close(pipefd[i][WRITE]);
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
		if (i > 0)
			close(pipefd[i - 1][READ]);
		if (i < mshell->n_cmds - 1)
			close(pipefd[i][WRITE]);
	}
	i = -1;
	while (++i < mshell->n_cmds)
	{
		waitpid(pid[i], &status, 0);
		if (i < mshell->n_cmds - 1)
		{
			close(pipefd[i][READ]);
			close(pipefd[i][WRITE]);
		}
	}
	free(pid);
	free(pipefd);
	if (!WTERMSIG(status))
		g_exit_status = WEXITSTATUS(status);
}
