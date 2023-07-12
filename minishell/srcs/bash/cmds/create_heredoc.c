/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:09:22 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 18:48:55 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	sigint_heredoc(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	exit(130);
}

void	continue_write(t_cmds *cmds, int fd, char *line)
{
	while (ft_strncmp(line, cmds->redin, ft_strlen(cmds->redin) + 1))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
}

void	child_heredoc(t_cmds *cmds)
{
	int		fd;
	char	*num;
	char	*name;
	char	*line;

	signal(SIGINT, &sigint_heredoc);
	num = ft_itoa(cmds->id);
	name = ft_strjoin("heredoc", num);
	free(num);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(name);
	line = readline("> ");
	if (line == NULL)
	{
		write(1, "\n", 1);
		exit(0);
	}
	continue_write(cmds, fd, line);
	close(fd);
	exit(0);
}

void	cr_heredoc(t_cmds *cmds)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		child_heredoc(cmds);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
