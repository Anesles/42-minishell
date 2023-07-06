/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:34 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:32:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bad_fd_error(t_cmds *cmds, char *str, int fd)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (cmds->fork == 1)
			exit(1);
		return (-1);
	}
	return (0);
}

int	token_less(t_cmds *cmds, int mode)
{
	int		fd;
	char	*line;

	if (mode == 0)
	{
		fd = open(cmds->redin, O_RDONLY);
		if (bad_fd_error(cmds, cmds->redin, fd) == -1)
			return (-1);
	}
	else
	{
		fd = open("temp", O_WRONLY | O_CREAT, 0644);
		if (bad_fd_error(cmds, cmds->redin, fd) == -1)
			return (-1);
		line = readline("> ");
		while (ft_strncmp(line, cmds->redin, ft_strlen(line)))
		{
			write(fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
			line = readline("> ");
		}
		close(fd);
		fd = open("temp", O_RDONLY);
	}
	dup_fd(fd);
	return (0);
}

void	token_more(t_cmds *cmds, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(cmds->redout, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(cmds->redout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_pipes(int num, int (*pipefd)[2], t_mshell *mshell)
{
	if (num == 0)
	{
		dup2(pipefd[num][WRITE], STDOUT_FILENO);
		close(pipefd[num][READ]);
		close(pipefd[num][WRITE]);
	}
	else if (num == mshell->n_cmds - 1)
	{
		dup2(pipefd[num - 1][READ], STDIN_FILENO);
		close(pipefd[num - 1][READ]);
		close(pipefd[num - 1][WRITE]);
	}
	else
	{
		dup2(pipefd[num - 1][READ], STDIN_FILENO);
		dup2(pipefd[num][WRITE], STDOUT_FILENO);
		close(pipefd[num - 1][READ]);
		close(pipefd[num - 1][WRITE]);
		close(pipefd[num][READ]);
		close(pipefd[num][WRITE]);
	}
}

void	reset_fds(t_mshell *mshell)
{
	dup2(mshell->res_pipes[READ], STDIN_FILENO);
	dup2(mshell->res_pipes[WRITE], STDOUT_FILENO);
}
