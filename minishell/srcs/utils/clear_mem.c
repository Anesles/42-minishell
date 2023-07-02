/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:16:29 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/02 18:14:07 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_cmds(t_cmds *cmds, int n_cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_cmds)
	{
		j = 0;
		while (cmds[i].words[j])
		{
			free(cmds[i].words[j]);
			j++;
		}
		free(cmds[i].words);
		if (cmds[i].redi != NULL)
		{
			free(cmds[i].redi);
			free(cmds[i].token);
		}
		i++;
	}
	free(cmds);
}

void	free_lexer(t_lexer *lexer, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lexer[i].word);
		i++;
	}
	free(lexer);
}

void	clear_mem(t_mshell *mshell, t_cmds *cmds)
{
	clear_cmds(cmds, mshell->n_cmds);
	unlink("temp");
}
