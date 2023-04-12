/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:44 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/12 15:18:21 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_lexer *lexer)
{
	int	count;
	t_lexer	*temp;

	temp = lexer;
	count = 1;
	while (temp)
	{
		if (temp->word == '|')
			count++;
		temp = temp->next;	
	}
	return (count);
}

void	init_cmds(t_lexer *lexer)
{
	t_cmds **cmds;

	cmds = malloc(sizeof(t_cmds *) * count_cmds(lexer));
	(void) cmds;	
}