/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:56:32 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:04:59 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alloc_words_aux(t_lexer *temp, t_cmds *cmds, int redir)
{
	int		i;
	char	**words;

	i = -1;
	words = malloc(sizeof(char *) * (cmds->count_words + 1));
	if (!words)
		return (NULL);
	while (++i < cmds->count_words)
	{
		words[i] = ft_strdup(temp->word);
		temp = temp->next;
	}
	words[i] = NULL;
	if (redir == 1)
	{
		cmds->token = ft_strdup(temp->word);
		temp = temp->next;
		cmds->redi = ft_strdup(temp->word);
	}
	else
	{
		cmds->token = NULL;
		cmds->redi = NULL;
	}
	return (words);
}

char	**alloc_words(t_lexer *lexer, t_cmds *cmds)
{
	char	**words;
	t_lexer	*temp;
	int		redir;

	cmds->count_words = 0;
	redir = 0;
	temp = lexer;
	while (temp)
	{
		if (temp->word[0] == '|')
			break ;
		if (is_redir(temp->word))
		{
			redir = 1;
			break ;
		}
		cmds->count_words++;
		temp = temp->next;
	}
	words = alloc_words_aux(lexer, cmds, redir);
	return (words);
}
