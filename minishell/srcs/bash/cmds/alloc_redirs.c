/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 00:41:48 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/06 19:08:18 by brumarti         ###   ########.fr       */
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

int	attr_redir(t_cmds *cmds, t_lexer *lexer, int mode)
{
	if (mode == 0)
	{
		if (cmds->tokenout != NULL)
			free(cmds->tokenout);
		cmds->tokenout = ft_strdup(lexer->word);
		lexer = lexer->next;
		if (cmds->redout != NULL)
			free(cmds->redout);
		cmds->redout = ft_strdup(lexer->word);
	}
	else if (attr_redir_in(cmds, lexer) == -1)
		return (-1);
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
				status = attr_redir(cmds, lexer, 0);
			else if (ft_strncmp(lexer->word, "<<", 2) == 0
				|| ft_strncmp(lexer->word, "<", 1) == 0)
				status = attr_redir(cmds, lexer, 1);
			if (check_status(status, lexer) == -1)
				return (-1);
		}
		free(lexer->word);
		lexer = lexer->next;
	}
	if (lexer && lexer->word[0] == '|')
		free(lexer->word);
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
			str = expand_env(cmds[i].redin, mshell);
			free(cmds[i].redin);
			cmds[i].redin = ft_strdup(str);
			free(str);
		}
		if (cmds[i].redout != NULL)
		{
			str = expand_env(cmds[i].redout, mshell);
			free(cmds[i].redout);
			cmds[i].redout = ft_strdup(str);
			free(str);
		}
		i++;
	}
}
