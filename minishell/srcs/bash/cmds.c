/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:44 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	count_cmds(t_lexer *lexer)
{
	int		count;
	t_lexer	*temp;

	temp = lexer;
	count = 1;
	while (temp)
	{
		if (temp->word[0] == '|' && temp->next != NULL)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	check_validcmd(t_cmds cmds)
{
	if (cmds.redi == NULL)
		return (0);
	if (cmds.redi[0] == '|' || cmds.redi[0] == '<' || cmds.redi[0] == '>')
	{
		g_exit_status = 2;
		ft_printf("syntax error near unexpected token '%s'\n", cmds.redi);
		return (1);
	}
	return (0);
}

int	alloc_cmds(t_cmds *cmds, int n, t_lexer *lexer)
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
		cmds[i].words = alloc_words(&lexer[start], &cmds[i], i, n);
		if (cmds[i].words == NULL && i == n - 1)
		{
			error_cd(NULL);
			return (-1);
		}
		if (check_validcmd(cmds[i]))
			return (-1);
		start += cmds[i].count_words + 1;
		if (cmds[i].token != NULL)
			start += 2;
	}
	return (0);
}

t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell)
{
	t_cmds	*cmds;
	int		n;

	n = count_cmds(lexer);
	mshell->n_cmds = n;
	mshell->current_cmd = -1;
	cmds = malloc(sizeof(t_cmds) * n);
	if (alloc_cmds(cmds, n, lexer) == -1)
	{
		g_exit_status = 1;
		free(cmds);
		return (NULL);
	}
	return (cmds);
}
