/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirs_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:57:30 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/06 18:33:14 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	attr_redir_in(t_cmds *cmds, t_lexer *lexer)
{
	if (cmds->tokenin != NULL)
		free(cmds->tokenin);
	cmds->tokenin = ft_strdup(lexer->word);
	lexer = lexer->next;
	if (cmds->redin != NULL)
		free(cmds->redin);
	cmds->redin = ft_strdup(lexer->word);
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
