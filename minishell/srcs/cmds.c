/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:44 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/24 17:04:44 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_lexer *lexer)
{
	int		count;
	t_lexer	*temp;

	temp = lexer;
	count = 1;
	while (temp)
	{
		if (temp->word[0] == '|')
			count++;
		temp = temp->next;
	}
	return (count);
}

char	**alloc_words(t_lexer *lexer, t_cmds *cmds)
{	
	char	**words;
	t_lexer	*temp;
	int		i;
	int		count;

	count = 0;
	temp = lexer;
	while (temp)
	{
		if (temp->word[0] == '|')
			break ;
		else
			count++;
		temp = temp->next;
	}
	cmds->count_words = count;
	words = malloc(sizeof(char *) * (count + 1));
	temp = lexer;
	i = -1;
	while (++i < count)
	{
		words[i] = temp->word;
		temp = temp->next;
	}
	words[i] = NULL;
	return (words);
}

void	alloc_cmds(t_cmds *cmds, int n, t_lexer *lexer)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	while (++i < n)
	{
		if (i == 0)
			cmds[i].prev = NULL;
		else
			cmds[i].prev = &cmds[i - 1];
		if (i == n - 1)
			cmds[i].next = NULL;
		else
			cmds[i].next = &cmds[i + 1];
		cmds[i].built = &builtins;
		cmds[i].words = alloc_words(&lexer[start], &cmds[i]);
		start += cmds[i].count_words + 1;
	}
}

t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell)
{
	t_cmds	*cmds;
	int		n;

	n = count_cmds(lexer);
	mshell->n_cmds = n;
	mshell->current_cmd = -1;
	cmds = malloc(sizeof(t_cmds) * n);
	alloc_cmds(cmds, n, lexer);
	return (cmds);
}