/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:59:23 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 12:45:00 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	less_aux(t_cmds *cmds)
{
	int		fd;
	char	*line;
	char	*str;

	fd = open("temp", O_WRONLY | O_CREAT, 0644);
	line = readline("> ");
	if (line == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (ft_strncmp(line, cmds->redin, ft_strlen(cmds->redin) + 1))
	{
		str = ft_strjoin(line, "\n");
		write(fd, str, ft_strlen(line) + 1);
		free(str);
		line = readline("> ");
	}
	close(fd);
}

void	sig_heredoc(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_exit_status = 130;	
	exit(130);
}

int	token_less(t_cmds *cmds, int mode)
{
	int		fd;

	if (mode == 0)
	{
		fd = open(cmds->redin, O_RDONLY);
		if (bad_fd_error(cmds, cmds->redin, fd) == -1)
			return (-1);
	}
	else
	{
		signal(SIGINT, &sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
		less_aux(cmds);
		fd = open("temp", O_RDONLY);
	}
	dup_fd(fd);
	return (0);
}
