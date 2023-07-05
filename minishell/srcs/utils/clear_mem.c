/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:16:29 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/05 19:38:31 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array[i]);
	free(array);
}

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
		if (cmds[i].redin)
			free(cmds[i].redin);
		if (cmds[i].tokenin)
			free(cmds[i].tokenin);
		if (cmds[i].redout)
		{
			free(cmds[i].redout);
			free(cmds[i].tokenout);
		}
		i++;
	}
	free(cmds);
}

void	free_envior(t_mshell *mshell)
{
	int	i;

	i = -1;
	while (mshell->envior[++i])
		free(mshell->envior[i]);
	free(mshell->envior[i]);
	free(mshell->envior);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp;

	temp = lexer;
	while (temp)
	{
		free(temp->word);
		temp = temp->next;
	}
	free(lexer);
}

void	clear_mem(t_mshell *mshell, t_cmds *cmds)
{
	clear_cmds(cmds, mshell->n_cmds);
	unlink("temp");
}
