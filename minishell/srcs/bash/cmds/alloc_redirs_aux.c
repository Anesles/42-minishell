/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirs_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:57:30 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/08 14:36:05 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	cr_heredoc(t_cmds *cmds)
{
	int		fd;
	char	*line;
	char	*str;

	fd = open("temp", O_WRONLY | O_CREAT, 0644);
	line = readline("> ");
	while (ft_strncmp(line, cmds->redin, ft_strlen(line)))
	{
		str = ft_strjoin(line, "\n");
		write(fd, str, ft_strlen(line) + 1);
		free(str);
		line = readline("> ");
	}
	close(fd);
}

int	attr_redir_in(t_cmds *cmds, t_lexer *lexer)
{
	t_lexer	*aux;

	if (cmds->tokenin != NULL)
	{
		if (ft_strncmp(cmds->tokenin, "<<", 2) == 0)
			cr_heredoc(cmds);
		free(cmds->tokenin);
	}
	cmds->tokenin = ft_strdup(lexer->word);
	aux = lexer->next;
	if (aux == NULL)
	{
		free(cmds->tokenin);
		return (-2);
	}
	if (cmds->next == NULL && !valid_redir(aux->word)
		&& ft_strncmp(cmds->tokenin, "<<", 2) != 0)
	{
		free(cmds->tokenin);
		if (cmds->redin != NULL)
			free(cmds->redin);
		return (-1);
	}
	if (cmds->redin != NULL)
		free(cmds->redin);
	cmds->redin = ft_strdup(aux->word);
	return (0);
}

int	check_status(int status, t_lexer *lexer)
{
	if (status == -1)
	{
		while (lexer)
		{
			free(lexer->word);
			lexer = lexer->next;
		}
		g_exit_status = 1;
		return (-1);
	}
	else if (status == -2)
	{
		while (lexer)
		{
			free(lexer->word);
			lexer = lexer->next;
		}
		g_exit_status = 2;
		return (-1);
	}
	return (0);
}
