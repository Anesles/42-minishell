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

char	**alloc_words_aux(t_lexer *lexer, t_cmds *cmds, int redir)
{
	int		i;
	int		j;
	t_lexer	*temp;
	char	**words;
	
	i = 0;
	j = 0;
	temp = lexer;
	words = malloc(sizeof(char *) * (cmds->count_words + 1));
	if (!words)
		return (NULL);
	while (j < cmds->count_words)
	{
		if (i == 0 || (i != redir && i != redir + 1))
		{
			words[j] = ft_strdup(temp->word);
			j++;
		}
		i++;
		temp = temp->next;
	}
	words[j] = NULL;
	if (redir > 0)
	{
		cmds->token = ft_strdup(lexer[redir].word);
		cmds->redi = ft_strdup(lexer[redir + 1].word);
	}
	else
	{
		cmds->token = NULL;
		cmds->redi = NULL;
	}
	return (words);
}

int	valid_redir(char *redi)
{
	DIR*	dir;
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

char	**alloc_words(t_lexer *lexer, t_cmds *cmds, int num, int max)
{
	char	**words;
	int		i;
	t_lexer	*temp;
	int		redir;

	cmds->count_words = 0;
	redir = -1;
	temp = lexer;
	i = 0;
	while (temp)
	{
		if (temp->word[0] == '|')
			break ;
		if (is_redir(temp->word))
		{
			redir = i;
			temp = temp->next;
			if (num == max - 1 && !valid_redir(temp->word))
				return (NULL);
			i++;
		}
		else
			cmds->count_words++;
		temp = temp->next;
		i++;
	}
	words = alloc_words_aux(lexer, cmds, redir);
	return (words);
}
