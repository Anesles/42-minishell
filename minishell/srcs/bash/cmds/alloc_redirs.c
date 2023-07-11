/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 00:41:48 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/11 01:03:32 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_redir(char *redi)
{
	DIR		*dir;
	char	*str;

	str = ft_strtrim(redi, "\"");
	dir = opendir(str);
	free(str);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	else if (ENOENT == errno)
		return (0);
	else
		return (1);
}

int	attr_redir_out(t_cmds *cmds, t_lexer *aux)
{
	int		fd;

	if (cmds->tokenout != NULL)
		free(cmds->tokenout);
	cmds->tokenout = ft_strdup(aux->word);
	aux = aux->next;
	if (aux == NULL)
	{
		free(cmds->tokenout);
		return (-2);
	}
	if (cmds->redout != NULL)
		free(cmds->redout);
	cmds->redout = ft_strdup(aux->word);
	fd = open(cmds->redout, O_CREAT | O_RDWR | O_APPEND, 0644);
	close(fd);
	return (0);
}

void	init_redir(t_cmds *cmds)
{
	cmds->tokenin = NULL;
	cmds->tokenout = NULL;
	cmds->redin = NULL;
	cmds->redout = NULL;
}

int	find_redir(t_lexer *lexer, t_cmds *cmds)
{
	int		status;

	init_redir(cmds);
	while (lexer && lexer->word[0] != '|')
	{
		if (is_redir(lexer->word))
		{
			if (ft_strncmp(lexer->word, ">>", 2) == 0
				|| ft_strncmp(lexer->word, ">", 1) == 0)
				status = attr_redir_out(cmds, lexer);
			else if (ft_strncmp(lexer->word, "<<", 2) == 0
				|| ft_strncmp(lexer->word, "<", 1) == 0)
				status = attr_redir_in(cmds, lexer);
			if (check_status(status) == -1)
			{
				while (lexer)
				{
					free(lexer->word);
					lexer = lexer->next;
				}
				return (-1);
			}
		}
		free(lexer->word);
		cmds->all_words++;
		lexer = lexer->next;
	}
	condit_redir(lexer);
	return (0);
}

void	fix_redir(t_cmds *cmds, t_mshell *mshell)
{
	char	*str;
	int		i;

	i = 0;
	while (i < mshell->n_cmds)
	{
		if (cmds[i].redin != NULL)
		{
			str = remove_quotes(cmds[i].redin);
			free(cmds[i].redin);
			cmds[i].redin = ft_strdup(str);
			free(str);
		}
		if (cmds[i].redout != NULL)
		{
			str = remove_quotes(cmds[i].redout);
			free(cmds[i].redout);
			cmds[i].redout = ft_strdup(str);
			free(str);
		}
		i++;
	}
}
