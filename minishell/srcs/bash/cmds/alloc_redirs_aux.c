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

int	attr_redir_in(t_cmds *cmds, t_lexer *lexer)
{
	t_lexer	*aux;

	if (cmds->tokenin != NULL)
		free(cmds->tokenin);
	cmds->tokenin = ft_strdup(lexer->word);
	aux = lexer->next;
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
		return (-1);
	}
	return (0);
}
