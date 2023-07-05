/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 00:41:48 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/05 02:19:33 by brumarti         ###   ########.fr       */
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
	t_lexer	*aux;

	if (mode == 0)
	{
		cmds->tokenout = ft_strdup(lexer->word);
		lexer = lexer->next;
		cmds->redout = ft_strdup(lexer->word);
	}
	else
	{
		cmds->tokenin = ft_strdup(lexer->word);
		aux = lexer->next;
		if (cmds->next == NULL && !valid_redir(aux->word))
		{
			free(lexer->word);
			free(cmds->tokenin);
			free(aux->word);
			return (-1);
		}
		cmds->redin = ft_strdup(lexer->word);
	}
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
	while (lexer)
	{
		if (is_redir(lexer->word))
		{
			if (ft_strncmp(lexer->word, ">>", 2) == 0
				|| ft_strncmp(lexer->word, ">", 1) == 0)
				status = attr_redir(cmds, lexer, 0);
			else if (ft_strncmp(lexer->word, "<<", 2) == 0
				|| ft_strncmp(lexer->word, "<", 1) == 0)
				status = attr_redir(cmds, lexer, 1);
			if (status == -1)
				return (-1);
		}
		free(lexer->word);
		lexer = lexer->next;
	}
	return (0);
}

void	fix_redir(t_cmds *cmds, t_mshell *mshell)
{
	char	*str;

	if (cmds->redin != NULL)
	{
		str = expand_env(cmds->redin, mshell);
		free(cmds->redin);
		cmds->redin = ft_strdup(str);
		free(str);
	}
	if (cmds->redout != NULL)
	{
		str = expand_env(cmds->redout, mshell);
		free(cmds->redout);
		cmds->redout = ft_strdup(str);
		free(str);
	}
}
