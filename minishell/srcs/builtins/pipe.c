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

void	token_less(t_cmds *cmds, int mode)
{
	int		fd;
	char	*line;

	if (mode == 0)
		fd = open(cmds->redi, O_RDONLY);
	else
	{
		fd = open("temp", O_WRONLY | O_CREAT, 0644);
		line = readline("> ");
		while (ft_strncmp(line, cmds->redi, ft_strlen(cmds->redi)))
		{
			write(fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
			line = readline("> ");
		}
		close(fd);
		fd = open("temp", O_RDONLY);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	token_more(t_cmds *cmds, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(cmds->redi, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(cmds->redi, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_pipe(t_mshell *mshell)
{
	if (mshell->current_cmd == 0)
	{
		close(mshell->fd[0]);
		dup2(mshell->fd[1], STDOUT_FILENO);
	}
	else if (mshell->current_cmd % 2 != 0)
	{
		close(mshell->fd[1]);
		dup2(mshell->fd[0], STDIN_FILENO);
		if (mshell->current_cmd != mshell->n_cmds - 1)
		{
			close(mshell->prev_fd[0]);
			dup2(mshell->prev_fd[1], STDOUT_FILENO);
		}
	}
	else if (mshell->current_cmd % 2 == 0)
	{
		close(mshell->prev_fd[1]);
		dup2(mshell->prev_fd[0], STDIN_FILENO);
		if (mshell->current_cmd != mshell->n_cmds - 1)
		{
			close(mshell->fd[0]);
			dup2(mshell->fd[1], STDOUT_FILENO);
		}
	}
}

void	reset_pipes(t_mshell *mshell)
{
	dup2(mshell->save_fd[0], STDIN_FILENO);
	dup2(mshell->save_fd[1], STDOUT_FILENO);
}
