/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:44 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/12 16:01:32 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_lexer **lexer)
{
	int	count;
	t_lexer	*temp;

	temp = lexer[0];
	count = 1;
	while (temp)
	{
		if (temp->word[0] == '|')
			count++;
		temp = temp->next;	
	}
	return (count);
}

char	**alloc_words(t_lexer *lexer)
{	
	char **words;
	t_lexer *temp;
	int	i;
	int	count;

	count = 0;
	temp = lexer;
	while (temp)
	{
		if (temp->word[0] == '|')
			break;
		else
			count++;
		temp = temp->next;
	}
	words = malloc(sizeof(char *) * count);
	temp = lexer;
	i = -1;
	while (++i < count)
	{
		words[i] = temp->word;
		temp = temp->next;
	}
	return (words);
}

void	alloc_cmds(t_cmds **cmds, int n, t_lexer **lexer)
{
	int	i;
	int	start;
	
	i = -1;
	while (++i < n)
		cmds[i] = malloc(sizeof(t_cmds));
	i = -1;
	start = 0;
	while(++i < n)
	{
		if (i == 0)
			cmds[i]->prev = NULL;
		else
			cmds[i]->prev = cmds[i - 1];
		if (i == n - 1)
			cmds[i]->next = NULL;
		else
			cmds[i]->next = cmds[i + 1];
		cmds[i]->words = alloc_words(lexer[start]);
		start = count_words(cmds[i]->words);
	}
}

void	init_cmds(t_lexer **lexer)
{
	t_cmds **cmds;
	t_cmds *temp;
	int	i;
	int	n;

	n = count_cmds(lexer);
	cmds = malloc(sizeof(t_cmds *) * n);
	alloc_cmds(cmds, n, lexer);
	temp = cmds[0];
	while (temp)
	{
		i = 0;
		while (i < 3)
		{
			ft_printf("%s\n", temp->words[i]);
			i++;
		}
		ft_printf("Cheguei !\n");
		temp = temp->next;
	}
}